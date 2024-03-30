// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/AttributeSets/SmartAIHealthSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

USmartAIHealthSet::USmartAIHealthSet()
{
	UE_LOG(LogTemp, Warning, TEXT("USmartAIHealthSet::USmartAIHealthSet - %s"), *GetClass()->GetName());
	InitHealth(100);
	InitMaxHealth(100);
}
void USmartAIHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USmartAIHealthSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USmartAIHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void USmartAIHealthSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USmartAIHealthSet, Health, OldValue);

	const float CurrentHealth = GetHealth();
	const float EstimatedMagnitude = CurrentHealth - OldValue.GetCurrentValue();

	OnHealthChanged.Broadcast(nullptr, nullptr, FGameplayEffectSpec(), EstimatedMagnitude, OldValue.GetCurrentValue(), CurrentHealth);

	if (!bOutOfHealth && CurrentHealth <= 0.0f)
	{
		OnOutOfHealth.Broadcast(nullptr, nullptr, FGameplayEffectSpec(), EstimatedMagnitude, OldValue.GetCurrentValue(), CurrentHealth);
	}

	bOutOfHealth = (CurrentHealth <= 0.0f);
}

void USmartAIHealthSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USmartAIHealthSet, MaxHealth, OldValue);
	
	OnMaxHealthChanged.Broadcast(nullptr, nullptr, FGameplayEffectSpec(), GetMaxHealth() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetMaxHealth());

}



bool USmartAIHealthSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}
	
	HealthBeforeAttributeChange = GetHealth();
	MaxHealthBeforeAttributeChange = GetMaxHealth();

	return true;
}

void USmartAIHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	SetHealth(FMath::Clamp(GetHealth() - GetDamage(), 0, GetMaxHealth()));
	
	bOutOfHealth = (GetHealth() <= 0.0f);
}

void USmartAIHealthSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void USmartAIHealthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void USmartAIHealthSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}
