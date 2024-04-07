// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MagnitudeCalc/GEECalculation_CalcDamage.h"

#include "Character/Abilities/AttributeSets/SmartAIDefenceSet.h"
#include "Character/Abilities/AttributeSets/SmartAIHealthSet.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Calculation_Damage, "Calculation.Damage");

struct FDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition DefencePercentDef;
	FDamageStatics()
	{
		DefencePercentDef = FGameplayEffectAttributeCaptureDefinition(USmartAIDefenceSet::GetDefencePercentAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
	}
};
static FDamageStatics GetStatics()
{
	static FDamageStatics Statics;
	return Statics; 
};
UGEECalculation_CalcDamage::UGEECalculation_CalcDamage()
{
	RelevantAttributesToCapture.Add(GetStatics().DefencePercentDef);
}

float UGEECalculation_CalcDamage::CaclulateDamage(const float Damage, const float DefencePercent) const
{
	return Damage - Damage * DefencePercent; 
}

void UGEECalculation_CalcDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                        FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluationParameters;
	
	float DefencePercent = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetStatics().DefencePercentDef, EvaluationParameters, DefencePercent);

	const float Damage = Spec.GetSetByCallerMagnitude(TAG_Calculation_Damage, false, 0.0f);

	const float CalculatedDamage = -CaclulateDamage(Damage, DefencePercent);
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USmartAIHealthSet::GetHealthAttribute(), EGameplayModOp::Additive, CalculatedDamage));
}
