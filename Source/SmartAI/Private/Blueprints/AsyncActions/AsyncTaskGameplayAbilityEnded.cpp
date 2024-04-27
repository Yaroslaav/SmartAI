// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprints/AsyncActions/AsyncTaskGameplayAbilityEnded.h"

UAsyncTaskGameplayAbilityEnded* UAsyncTaskGameplayAbilityEnded::ListenForGameplayAbilityEnd(UAbilitySystemComponent* abilitySystemComponent,  TSubclassOf<UGameplayAbility> abilityClass)
{
	if (!IsValid(abilitySystemComponent))
	{
		UE_LOG( LogTemp, Warning, TEXT("Couldnt create Task, missing ASC"));
		return nullptr;
	}
	
	const UGameplayAbility* const abilityDef = abilityClass.GetDefaultObject();
	if (abilityDef == nullptr)
	{

		UE_LOG( LogTemp, Warning, TEXT("Couldnt create Task, Ability %s CDO is invalid"), *abilityClass->GetName());
		return nullptr;
	}
	
	if (abilityDef->AbilityTags.IsValid() == false)
	{
		UE_LOG( LogTemp, Warning, TEXT("Couldnt create Task, Ability %s has no AbilityTags"), *abilityClass->GetName());
		return nullptr;
	}
	
	UAsyncTaskGameplayAbilityEnded* r = NewObject<UAsyncTaskGameplayAbilityEnded>();
	r->ASC = abilitySystemComponent;
	r->TagsStillApplied = abilityDef->AbilityTags;

	for (const auto tag : r->TagsStillApplied)
	{
		auto h = abilitySystemComponent->RegisterGameplayTagEvent(tag, EGameplayTagEventType::NewOrRemoved).AddUObject(r, &UAsyncTaskGameplayAbilityEnded::OnCallback);
		r->HandlesMap.Add(tag, h);
	}

	return r;
}

void UAsyncTaskGameplayAbilityEnded::EndTask()
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

void UAsyncTaskGameplayAbilityEnded::OnCallback(const FGameplayTag CallbackTag, int32 NewCount)
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