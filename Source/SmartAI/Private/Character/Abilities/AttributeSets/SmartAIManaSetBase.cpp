// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/AttributeSets/SmartAIManaSetBase.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

USmartAIManaSetBase::USmartAIManaSetBase()
{
	UE_LOG( LogTemp, Warning, TEXT( "USmartAIManaSetBase::USmartAIManaSetBase()"));
	InitMana(500);
	InitMaxMana(500);
}
void USmartAIManaSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USmartAIManaSetBase, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USmartAIManaSetBase, MaxMana, COND_None, REPNOTIFY_Always);
}
void USmartAIManaSetBase::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USmartAIManaSetBase, Mana, OldValue);
}

void USmartAIManaSetBase::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USmartAIManaSetBase, MaxMana, OldValue);
}

bool USmartAIManaSetBase::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if(!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	ManaBeforeAttributeChange = GetMana();
	MaxManaBeforeAttributeChange = GetMaxMana();
	
	return true;
}

void USmartAIManaSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if(GetMana() != ManaBeforeAttributeChange)
	{
		OnManaChanged.Broadcast(nullptr, nullptr, FGameplayEffectSpec(), GetMana() - ManaBeforeAttributeChange, ManaBeforeAttributeChange, GetMana());
	}
	if(GetMaxMana() != MaxManaBeforeAttributeChange)
	{
		OnMaxManaChanged.Broadcast(nullptr, nullptr, FGameplayEffectSpec(), GetMaxMana() - MaxManaBeforeAttributeChange , MaxManaBeforeAttributeChange, GetMaxMana());
	}
	SetMana(FMath::Clamp(GetMana() - Data.EvaluatedData.Magnitude, 0, GetMaxMana()));
}

void USmartAIManaSetBase::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttribute(Attribute,NewValue);
}

void USmartAIManaSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttribute(Attribute,NewValue);
}

void USmartAIManaSetBase::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if(Attribute == GetMaxManaAttribute())
	{
		if(GetMana() > NewValue)
		{
			UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
			check( ASC );
			ASC->ApplyModToAttribute( GetManaAttribute(), EGameplayModOp::Override, NewValue);
		}
	}
}

void USmartAIManaSetBase::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}else if(Attribute == GetMaxManaAttribute())
	{
		NewValue = FMath::Max(NewValue,1.0f);
	}
}
