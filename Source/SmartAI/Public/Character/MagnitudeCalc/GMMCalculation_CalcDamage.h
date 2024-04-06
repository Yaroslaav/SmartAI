// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GMMCalculation_CalcDamage.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API UGMMCalculation_CalcDamage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UGMMCalculation_CalcDamage();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
	FGameplayEffectAttributeCaptureDefinition DefencePercentDef;
};
