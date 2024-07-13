// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SmartAIAbilitySystemComponent.generated.h"


class UInputAction;

USTRUCT()
struct FAbilityInputBinding
{
	GENERATED_BODY()

	int32  InputID = 0;
	uint32 OnPressedHandle = 0;
	uint32 OnReleasedHandle = 0;
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack;
};

/**
 * 
 */
UCLASS()
class SMARTAI_API USmartAIAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USmartAIAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Ability")
	FGameplayAbilitySpecContainer GetActivatableAbilities() const;
	
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void LevelUpAbility(FGameplayAbilitySpecHandle AbilityHandle, int32 LevelMagnitude);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool IsAbilityActive(FGameplayAbilitySpecHandle AbilityHandle) const;
	
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void SetInputBinding(UInputAction* InputAction, FGameplayAbilitySpecHandle AbilityHandle);
	
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void SetInputBindingToPlayerController(UInputAction* InputAction, FGameplayAbilitySpecHandle AbilityHandle);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearInputBinding(FGameplayAbilitySpecHandle AbilityHandle);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearAbilityBindings(UInputAction* InputAction);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void TryCancelAbilitySpec(FGameplayAbilitySpecHandle AbilityToCancel);
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void CancelAllAbilitiesWithTags(FGameplayTagContainer Tags);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool ActivateAbilityWithEventData(TSubclassOf<UGameplayAbility> AbilityToActivate, FGameplayEventData EventData);
private:
	void OnAbilityInputPressed(UInputAction* InputAction);

	void OnAbilityInputReleased(UInputAction* InputAction);

	void RemoveEntry(UInputAction* InputAction);

	void TryBindAbilityInput(UInputAction* InputAction, FAbilityInputBinding& AbilityInputBinding, UEnhancedInputComponent* InputComponent);
	


	virtual void BeginPlay() override;

	UPROPERTY(transient)
	TMap<UInputAction*, FAbilityInputBinding> MappedAbilities;

	UPROPERTY(transient)
	UEnhancedInputComponent* OwnerInputComponent;
	
	UPROPERTY(transient)
	UEnhancedInputComponent* PlayerControllerInputComponent;
};
