// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/AttributeSets/SmartAIManaSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

USmartAIManaSet::USmartAIManaSet()
{
	UE_LOG( LogTemp, Warning, TEXT( "USmartAIManaSet::USmartAIManaSet()"));
	InitMana(500);
	InitMaxMana(500);
}

void USmartAIManaSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USmartAIManaSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USmartAIManaSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void USmartAIManaSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USmartAIManaSet, Mana, OldValue);
}

void USmartAIManaSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USmartAIManaSet, MaxMana, OldValue);

}

bool USmartAIManaSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if(!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	ManaBeforeAttributeChange = GetMana();
	MaxManaBeforeAttributeChange = GetMaxMana();
	
	return true;
}

void USmartAIManaSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
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
	//SetMana(FMath::Clamp(GetMana() - Data.EvaluatedData.Magnitude, 0, GetMaxMana()));

}

void USmartAIManaSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttribute(Attribute,NewValue);

}

void USmartAIManaSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttribute(Attribute,NewValue);

}

void USmartAIManaSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	/*if(Attribute == GetMaxManaAttribute())
	{
		if(GetMana() > NewValue)
		{
			UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
			check( ASC );
			ASC->ApplyModToAttribute( GetManaAttribute(), EGameplayModOp::Override, NewValue);
		}
	}*/

}

void USmartAIManaSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}else if(Attribute == GetMaxManaAttribute())
	{
		NewValue = FMath::Max(NewValue,1.0f);
	}
}
