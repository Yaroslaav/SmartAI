// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "NativeGameplayTags.h"
#include "GEECalculation_CalcDamage.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Calculation_Damage);
/**
 * 
 */
UCLASS()
class SMARTAI_API UGEECalculation_CalcDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGEECalculation_CalcDamage();
	float CalculateDamage(float Damage, const float DefencePercent, const float DamageBonus) const;
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
