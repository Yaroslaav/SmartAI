// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MagnitudeCalc/GMMCalculation_CalcDamage.h"

#include "Character/Abilities/AttributeSets/SmartAIDefenceSet.h"
#include "Character/Abilities/AttributeSets/SmartAIHealthSet.h"

UGMMCalculation_CalcDamage::UGMMCalculation_CalcDamage()
{

	DefencePercentDef.AttributeToCapture = USmartAIDefenceSet::GetDefencePercentAttribute();
	DefencePercentDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	DefencePercentDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(DefencePercentDef);
}

float UGMMCalculation_CalcDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float DefencePercent = 0.0f;
	GetCapturedAttributeMagnitude(DefencePercentDef, Spec, EvaluationParameters, DefencePercent);
	
	
	return 1.0f;
}
