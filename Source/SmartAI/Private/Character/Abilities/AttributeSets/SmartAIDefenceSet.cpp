// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/AttributeSets/SmartAIDefenceSet.h"

#include "Net/UnrealNetwork.h"

USmartAIDefenceSet::USmartAIDefenceSet()
{
	InitDefencePercent(0.0f);
}
void USmartAIDefenceSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USmartAIDefenceSet, DefencePercent, COND_None, REPNOTIFY_Always);
}
void USmartAIDefenceSet::OnRep_DefencePercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USmartAIDefenceSet, DefencePercent, OldValue);
}

bool USmartAIDefenceSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if(!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}
	
	DefencePercentBeforeAttributeChange = GetDefencePercent();
	return true;
}

void USmartAIDefenceSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void USmartAIDefenceSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void USmartAIDefenceSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void USmartAIDefenceSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}
