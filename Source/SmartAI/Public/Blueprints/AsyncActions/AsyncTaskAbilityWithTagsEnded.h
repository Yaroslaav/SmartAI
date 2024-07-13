// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "AsyncTaskAbilityWithTagsEnded.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncTaskGameplayAbilityWithTagsEndedEv);
/**
 * 
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class SMARTAI_API UAsyncTaskAbilityWithTagsEnded : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintAssignable)
	FAsyncTaskGameplayAbilityWithTagsEndedEv OnEnded;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskAbilityWithTagsEnded* ListenForGameplayAbilityEnd(UAbilitySystemComponent* abilitySystemComponent, TSubclassOf<UGameplayAbility> AbilityClass);
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskAbilityWithTagsEnded* ListenForGameplayAbilityEndByTags(UAbilitySystemComponent* abilitySystemComponent, FGameplayTagContainer WithTags);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	UAbilitySystemComponent* ASC;
	FGameplayTagContainer TagsStillApplied;
	TMap<FGameplayTag, FDelegateHandle> HandlesMap;

	UFUNCTION()
	virtual void OnCallback(const FGameplayTag CallbackTag, int32 NewCount);

};
