// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SmartAIGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API USmartAIGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	USmartAIGameplayAbility(const FObjectInitializer& ObjectInitializer);
	TArray<FAbilityTriggerData> GetAbilityTriggers() const;
};
