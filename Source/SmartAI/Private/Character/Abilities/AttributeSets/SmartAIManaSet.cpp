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
