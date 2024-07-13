// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/SmartAIGameplayAbility.h"

USmartAIGameplayAbility::USmartAIGameplayAbility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

TArray<FAbilityTriggerData> USmartAIGameplayAbility::GetAbilityTriggers() const
{
	return AbilityTriggers;
}
