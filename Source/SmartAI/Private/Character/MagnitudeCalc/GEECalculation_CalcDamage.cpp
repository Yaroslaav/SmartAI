// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MagnitudeCalc/GEECalculation_CalcDamage.h"

#include "Character/Abilities/AttributeSets/SmartAIDefenceSet.h"
#include "Character/Abilities/AttributeSets/SmartAIHealthSet.h"

struct FDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition DefencePercentDef;
	FDamageStatics()
	{
		DefencePercentDef = FGameplayEffectAttributeCaptureDefinition(USmartAIDefenceSet::GetDefencePercentAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
	}
};
static FDamageStatics GetStatic()
{
	static FDamageStatics Statics;
	return Statics; 
};
UGEECalculation_CalcDamage::UGEECalculation_CalcDamage()
{
	RelevantAttributesToCapture.Add(GetStatic().DefencePercentDef);
}

float UGEECalculation_CalcDamage::CaclulateDamage(float Damege, float DefencePercent) const
{
	return Damege - Damege * DefencePercent; 
}

void UGEECalculation_CalcDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                        FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluationParameters;
	
	float DefencePercent = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetStatic().DefencePercentDef, EvaluationParameters, DefencePercent);

	float Damage = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Calculation.Damage"), false), false, 0.0f);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USmartAIHealthSet::GetHealthAttribute(), EGameplayModOp::Additive, -CaclulateDamage(Damage, DefencePercent)));
}
