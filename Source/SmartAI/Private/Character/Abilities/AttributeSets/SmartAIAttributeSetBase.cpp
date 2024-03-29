// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/AttributeSets/SmartAIAttributeSetBase.h"


USmartAIAttributeSetBase::USmartAIAttributeSetBase()
{
}

UWorld* USmartAIAttributeSetBase::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}


