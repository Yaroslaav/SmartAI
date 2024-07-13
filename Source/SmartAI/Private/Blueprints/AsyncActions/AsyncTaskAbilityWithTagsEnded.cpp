// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprints/AsyncActions/AsyncTaskAbilityWithTagsEnded.h"

UAsyncTaskAbilityWithTagsEnded* UAsyncTaskAbilityWithTagsEnded::ListenForGameplayAbilityEnd(
	UAbilitySystemComponent* abilitySystemComponent, TSubclassOf<UGameplayAbility> AbilityClass)
{
	if (!IsValid(abilitySystemComponent))
	{
		UE_LOG( LogTemp, Warning, TEXT("Couldnt create Task, missing ASC"));
		return nullptr;
	}
	
	FGameplayAbilitySpec AbilitySpec = nullptr;
	const UGameplayAbility* const InAbilityCDO = AbilityClass.GetDefaultObject();

	
	for (FGameplayAbilitySpec& Spec : abilitySystemComponent->GetActivatableAbilities())
	{
		if (Spec.Ability == InAbilityCDO)
		{
			AbilitySpec = Spec;
			break;
		}
	}
	if(!AbilitySpec.Ability)
	{
		UE_LOG( LogTemp, Warning, TEXT("Couldnt create Task, missing Ability"));
		return nullptr;
	}
	FGameplayTagContainer abilityTags = AbilitySpec.Ability->AbilityTags;
	if (abilityTags.IsValid() == false)
	{
		UE_LOG( LogTemp, Warning, TEXT("Couldnt create Task, AbilityTags is invalid"));
		return nullptr;
	}
	
	UAsyncTaskAbilityWithTagsEnded* r = NewObject<UAsyncTaskAbilityWithTagsEnded>();
	r->ASC = abilitySystemComponent;
	r->TagsStillApplied = abilityTags;

	if(!abilitySystemComponent->HasAllMatchingGameplayTags(abilityTags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldnt create Task, AbilityTags are not present on ASC"));
		r->EndTask();
		return r;
	}
	for (const auto tag : r->TagsStillApplied)
	{
		auto h = abilitySystemComponent->RegisterGameplayTagEvent(tag, EGameplayTagEventType::NewOrRemoved).AddUObject(r, &UAsyncTaskAbilityWithTagsEnded::OnCallback);
		r->HandlesMap.Add(tag, h);
	}

	return r;

}

UAsyncTaskAbilityWithTagsEnded* UAsyncTaskAbilityWithTagsEnded::ListenForGameplayAbilityEndByTags(
	UAbilitySystemComponent* abilitySystemComponent, FGameplayTagContainer WithTags)
{
	if (!IsValid(abilitySystemComponent))
	{
		UE_LOG( LogTemp, Warning, TEXT("Couldnt create Task, missing ASC"));
		return nullptr;
	}
	
	UAsyncTaskAbilityWithTagsEnded* r = NewObject<UAsyncTaskAbilityWithTagsEnded>();
	r->ASC = abilitySystemComponent;
	r->TagsStillApplied = WithTags;

	if(!abilitySystemComponent->HasAllMatchingGameplayTags(WithTags))
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldnt create Task, AbilityTags are not present on ASC"));
		r->EndTask();
		return r;
	}
	for (const auto tag : r->TagsStillApplied)
	{
		auto h = abilitySystemComponent->RegisterGameplayTagEvent(tag, EGameplayTagEventType::NewOrRemoved).AddUObject(r, &UAsyncTaskAbilityWithTagsEnded::OnCallback);
		r->HandlesMap.Add(tag, h);
	}

	return r;
}

void UAsyncTaskAbilityWithTagsEnded::EndTask()
{
	if (IsValid(ASC))
	{
		for (const auto tag : TagsStillApplied)
		{
			ASC->UnregisterGameplayTagEvent(*HandlesMap.Find(tag), tag, EGameplayTagEventType::NewOrRemoved);
		}
	}

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UAsyncTaskAbilityWithTagsEnded::OnCallback(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount == 0) {
		if (TagsStillApplied.HasTagExact(CallbackTag))
		{
			TagsStillApplied.RemoveTag(CallbackTag);
			ASC->UnregisterGameplayTagEvent(*HandlesMap.Find(CallbackTag), CallbackTag, EGameplayTagEventType::NewOrRemoved);

			if (TagsStillApplied.IsEmpty())
			{
				OnEnded.Broadcast();
			}
		}
	}

}
