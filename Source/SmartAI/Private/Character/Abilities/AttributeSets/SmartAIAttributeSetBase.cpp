// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/AttributeSets/SmartAIAttributeSetBase.h"


USmartAIAttributeSetBase::USmartAIAttributeSetBase()
{
}

void USmartAIAttributeSetBase::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	ClampAttribute(Attribute, NewValue);
}

void USmartAIAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void USmartAIAttributeSetBase::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	
}

UWorld* USmartAIAttributeSetBase::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}


