// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "AsyncTaskGameplayAbilityEnded.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncTaskGameplayAbilityEndedEv);
/**
 * 
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))

class SMARTAI_API UAsyncTaskGameplayAbilityEnded : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintAssignable)
	FAsyncTaskGameplayAbilityEndedEv OnEnded;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncTaskGameplayAbilityEnded* ListenForGameplayAbilityEnd(UAbilitySystemComponent* abilitySystemComponent, TSubclassOf<UGameplayAbility> abilityClass);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	UAbilitySystemComponent* ASC;
	FGameplayTagContainer TagsStillApplied;
	TMap<FGameplayTag, FDelegateHandle> HandlesMap;

	UFUNCTION()
	virtual void OnCallback(const FGameplayTag CallbackTag, int32 NewCount);
};
