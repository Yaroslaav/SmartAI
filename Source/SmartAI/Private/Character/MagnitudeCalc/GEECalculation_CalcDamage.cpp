// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MagnitudeCalc/GEECalculation_CalcDamage.h"

#include "Character/Abilities/AttributeSets/SmartAIDefenceSet.h"
#include "Character/Abilities/AttributeSets/SmartAIHealthSet.h"
#include "Character/Abilities/AttributeSets/SmartAIStatsSet.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Calculation_Damage, "Calculation.Damage");

struct FDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition DefencePercentDef;
	FGameplayEffectAttributeCaptureDefinition DamageBonusDef;
	FGameplayEffectAttributeCaptureDefinition ReflectDamagePercentDef;
	FDamageStatics()
	{
		DefencePercentDef = FGameplayEffectAttributeCaptureDefinition(USmartAIDefenceSet::GetDefencePercentAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
		DamageBonusDef = FGameplayEffectAttributeCaptureDefinition(USmartAIStatsSet::GetDamageBonusAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
		ReflectDamagePercentDef = FGameplayEffectAttributeCaptureDefinition(USmartAIStatsSet::GetReflectDamagePercentAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
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
	RelevantAttributesToCapture.Add(GetStatics().DamageBonusDef);
	RelevantAttributesToCapture.Add(GetStatics().ReflectDamagePercentDef);
}

float UGEECalculation_CalcDamage::CalculateDamage(float Damage, const float DefencePercent, const float DamageBonus, const float ReflectDamagePercent) const
{
	//UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);
	Damage += Damage * DamageBonus;
	Damage -= Damage * ReflectDamagePercent;
	//UE_LOG(LogTemp, Warning, TEXT("Damage reflect: %f"), Damage * ReflectDamagePercent);

	return Damage - Damage * DefencePercent; 
}

void UGEECalculation_CalcDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                        FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FAggregatorEvaluateParameters EvaluationParameters;
	
	float DefencePercent = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetStatics().DefencePercentDef, EvaluationParameters, DefencePercent);

	float DamageBonus = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetStatics().DamageBonusDef, EvaluationParameters, DamageBonus);

	float ReflectDamagePercent = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetStatics().ReflectDamagePercentDef, EvaluationParameters, ReflectDamagePercent);

	const float Damage = Spec.GetSetByCallerMagnitude(TAG_Calculation_Damage, false, 0.0f);

	const float CalculatedDamage = -CalculateDamage(Damage, DefencePercent, DamageBonus, ReflectDamagePercent);

	UE_LOG(LogTemp, Warning, TEXT("Calc Damage: %f"), CalculatedDamage);
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(USmartAIHealthSet::GetHealthAttribute(), EGameplayModOp::Additive, CalculatedDamage));
}
