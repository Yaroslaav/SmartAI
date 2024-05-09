// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprints/AsyncActions/AsyncTaskAbilityWithTagsEnded.h"

UAsyncTaskAbilityWithTagsEnded* UAsyncTaskAbilityWithTagsEnded::ListenForGameplayAbilityEnd(
	UAbilitySystemComponent* abilitySystemComponent, FGameplayTagContainer abilityTags)
{
	if (!IsValid(abilitySystemComponent))
	{
		UE_LOG( LogTemp, Warning, TEXT("Couldnt create Task, missing ASC"));
		return nullptr;
	}
	
	
	if (abilityTags.IsValid() == false)
	{
		UE_LOG( LogTemp, Warning, TEXT("Couldnt create Task, AbilityTags is invalid"));
		return nullptr;
	}
	
	UAsyncTaskAbilityWithTagsEnded* r = NewObject<UAsyncTaskAbilityWithTagsEnded>();
	r->ASC = abilitySystemComponent;
	r->TagsStillApplied = abilityTags;

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
