// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/SmartAIAbilitySystemComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Character/Abilities/SmartAIGameplayAbility.h"

namespace EnhancedInputAbilitySystem_Impl
{
	constexpr int32 InvalidInputID = 0;
	int32 IncrementingInputID = InvalidInputID;

	static int32 GetNextInputID()
	{
		return ++IncrementingInputID;
	}
}

USmartAIAbilitySystemComponent::USmartAIAbilitySystemComponent(const FObjectInitializer& ObjectInitializer)
{
	
}

FGameplayAbilitySpecContainer USmartAIAbilitySystemComponent::GetActivatableAbilities() const
{
	return ActivatableAbilities;
}


void USmartAIAbilitySystemComponent::LevelUpAbility(FGameplayAbilitySpecHandle AbilityHandle, int32 LevelMagnitude)
{
	if(FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(AbilityHandle))
	{
		AbilitySpec->Level += LevelMagnitude;
		MarkAbilitySpecDirty(*AbilitySpec);
		
		if (!AbilitySpec->Ability->IsInstantiated())
		{
			UE_LOG(LogTemp, Error, TEXT("NOT INSTANTIATED"))
		}
	}
}

bool USmartAIAbilitySystemComponent::IsAbilityActive(FGameplayAbilitySpecHandle AbilityHandle) const
{
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(AbilityHandle);
	if(AbilitySpec == nullptr)
	{
		return false;
	}
	return AbilitySpec->IsActive();
}

void USmartAIAbilitySystemComponent::SetInputBinding(UInputAction* InputAction,
                                                     FGameplayAbilitySpecHandle AbilityHandle)
{
	using namespace EnhancedInputAbilitySystem_Impl;

	FGameplayAbilitySpec* BindingAbility = FindAbilitySpecFromHandle(AbilityHandle);

	FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);
	if (AbilityInputBinding)
	{
		FGameplayAbilitySpec* OldBoundAbility = FindAbilitySpecFromHandle(AbilityInputBinding->BoundAbilitiesStack.Top());
		if (OldBoundAbility && OldBoundAbility->InputID == AbilityInputBinding->InputID)
		{
			OldBoundAbility->InputID = InvalidInputID;
		}
	}
	else
	{
		AbilityInputBinding = &MappedAbilities.Add(InputAction);
		AbilityInputBinding->InputID = GetNextInputID();
	}

	if (BindingAbility)
	{
		BindingAbility->InputID = AbilityInputBinding->InputID;
	}

	AbilityInputBinding->BoundAbilitiesStack.Push(AbilityHandle);
	TryBindAbilityInput(InputAction, *AbilityInputBinding, OwnerInputComponent);
}

void USmartAIAbilitySystemComponent::SetInputBindingToPlayerController(UInputAction* InputAction,
	FGameplayAbilitySpecHandle AbilityHandle)
{
	using namespace EnhancedInputAbilitySystem_Impl;

	if(GetOwner() == nullptr)
	{
		return;
		
	}
	FGameplayAbilitySpec* BindingAbility = FindAbilitySpecFromHandle(AbilityHandle);

	FAbilityInputBinding* AbilityInputBinding = MappedAbilities.Find(InputAction);
	if (AbilityInputBinding)
	{
		FGameplayAbilitySpec* OldBoundAbility = FindAbilitySpecFromHandle(AbilityInputBinding->BoundAbilitiesStack.Top());
		if (OldBoundAbility && OldBoundAbility->InputID == AbilityInputBinding->InputID)
		{
			OldBoundAbility->InputID = InvalidInputID;
		}
	}
	else
	{
		AbilityInputBinding = &MappedAbilities.Add(InputAction);
		AbilityInputBinding->InputID = GetNextInputID();
	}

	if (BindingAbility)
	{
		BindingAbility->InputID = AbilityInputBinding->InputID;
	}

	AbilityInputBinding->BoundAbilitiesStack.Push(AbilityHandle);
	TryBindAbilityInput(InputAction, *AbilityInputBinding, PlayerControllerInputComponent);

}

void USmartAIAbilitySystemComponent::ClearInputBinding(FGameplayAbilitySpecHandle AbilityHandle)
{
	using namespace EnhancedInputAbilitySystem_Impl;

	if (FGameplayAbilitySpec* FoundAbility = FindAbilitySpecFromHandle(AbilityHandle))
	{
		// Find the mapping for this ability
		auto MappedIterator = MappedAbilities.CreateIterator();
		while (MappedIterator)
		{
			if (MappedIterator.Value().InputID == FoundAbility->InputID)
			{
				break;
			}
			++MappedIterator;
		}

		if (MappedIterator)
		{
			FAbilityInputBinding& AbilityInputBinding = MappedIterator.Value();

			if (AbilityInputBinding.BoundAbilitiesStack.Remove(AbilityHandle) > 0)
			{
				if (AbilityInputBinding.BoundAbilitiesStack.Num() > 0)
				{
					FGameplayAbilitySpec* StackedAbility = FindAbilitySpecFromHandle(AbilityInputBinding.BoundAbilitiesStack.Top());
					if (StackedAbility && StackedAbility->InputID == 0)
					{
						StackedAbility->InputID = AbilityInputBinding.InputID;
					}
				}
				else
				{
					// NOTE: This will invalidate the `AbilityInputBinding` ref above
					RemoveEntry(MappedIterator.Key());
				}
				// DO NOT act on `AbilityInputBinding` after here (it could have been removed)


				FoundAbility->InputID = InvalidInputID;
			}
		}
	}
}

void USmartAIAbilitySystemComponent::ClearAbilityBindings(UInputAction* InputAction)
{
	RemoveEntry(InputAction);
}

void USmartAIAbilitySystemComponent::TryCancelAbilitySpec(FGameplayAbilitySpecHandle AbilityToCancel)
{
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(AbilityToCancel);
	if (AbilitySpec)
	{
		CancelAbilitySpec(*AbilitySpec, AbilitySpec->Ability);
	}
}

void USmartAIAbilitySystemComponent::CancelAllAbilitiesWithTags(FGameplayTagContainer Tags)
{
	ApplyAbilityBlockAndCancelTags( FGameplayTagContainer(), nullptr, false, FGameplayTagContainer(), false, Tags );
}

bool USmartAIAbilitySystemComponent::ActivateAbilityWithEventData(TSubclassOf<UGameplayAbility> AbilityToActivate,
                                                                  FGameplayEventData EventData)
{
	FGameplayAbilitySpec AbilitySpec = nullptr;
	const UGameplayAbility* const InAbilityCDO = AbilityToActivate.GetDefaultObject();

	
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		if (Spec.Ability == InAbilityCDO)
		{
			AbilitySpec = Spec;
			break;
		}
	}
	if(!AbilitySpec.Ability)
	{
		return false;
	}
	const USmartAIGameplayAbility* SmartAIAbility = Cast<USmartAIGameplayAbility>(AbilitySpec.Ability);
	if( !SmartAIAbility )
	{
		return false;
	}
	FScopedPredictionWindow NewScopedWindow(this, true);
	return HandleGameplayEvent(SmartAIAbility->GetAbilityTriggers()[0].TriggerTag, &EventData) > 0;
}


void USmartAIAbilitySystemComponent::OnAbilityInputPressed(UInputAction* InputAction)
{
	using namespace EnhancedInputAbilitySystem_Impl;

	FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
	if (FoundBinding && ensure(FoundBinding->InputID != InvalidInputID))
	{
		AbilityLocalInputPressed(FoundBinding->InputID);
	}
}

void USmartAIAbilitySystemComponent::OnAbilityInputReleased(UInputAction* InputAction)
{
	using namespace EnhancedInputAbilitySystem_Impl;

	FAbilityInputBinding* FoundBinding = MappedAbilities.Find(InputAction);
	if (FoundBinding && ensure(FoundBinding->InputID != InvalidInputID))
	{
		AbilityLocalInputReleased(FoundBinding->InputID);
	}
}

void USmartAIAbilitySystemComponent::RemoveEntry(UInputAction* InputAction)
{
	
	if (FAbilityInputBinding* Bindings = MappedAbilities.Find(InputAction))
	{
		if (OwnerInputComponent)
		{
			OwnerInputComponent->RemoveBindingByHandle(Bindings->OnPressedHandle);
			OwnerInputComponent->RemoveBindingByHandle(Bindings->OnReleasedHandle);
		}

		for (FGameplayAbilitySpecHandle AbilityHandle : Bindings->BoundAbilitiesStack)
		{
			using namespace EnhancedInputAbilitySystem_Impl;

			FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(AbilityHandle);
			if (AbilitySpec && AbilitySpec->InputID == Bindings->InputID)
			{
				AbilitySpec->InputID = InvalidInputID;
			}
		}

		MappedAbilities.Remove(InputAction);
	}

}



void USmartAIAbilitySystemComponent::TryBindAbilityInput(UInputAction* InputAction, FAbilityInputBinding& AbilityInputBinding, UEnhancedInputComponent* InputComponent)
{
	
	if (InputComponent)
	{
		// Pressed event
		if (AbilityInputBinding.OnPressedHandle == 0)
		{
			AbilityInputBinding.OnPressedHandle = InputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &USmartAIAbilitySystemComponent::OnAbilityInputPressed, InputAction).GetHandle();
		}

		// Released event
		if (AbilityInputBinding.OnReleasedHandle == 0)
		{
			AbilityInputBinding.OnReleasedHandle = InputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &USmartAIAbilitySystemComponent::OnAbilityInputReleased, InputAction).GetHandle();
		}
	}

}

void USmartAIAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if (IsValid(Owner)) 
	{
		if(Owner->InputComponent)
		{
			OwnerInputComponent = CastChecked<UEnhancedInputComponent>(Owner->InputComponent);
		}
		if(GetWorld()->GetFirstPlayerController()->InputComponent)
		{
			PlayerControllerInputComponent = CastChecked<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->InputComponent);
		}
	}
}
