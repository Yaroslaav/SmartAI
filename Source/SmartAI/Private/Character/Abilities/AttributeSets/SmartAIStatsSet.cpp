// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/AttributeSets/SmartAIStatsSet.h"

USmartAIStatsSet::USmartAIStatsSet()
{
}

void USmartAIStatsSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::ClampAttribute(Attribute, NewValue);
}
