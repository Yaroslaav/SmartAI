// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Abilities/AttributeSets/SmartAIAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "SmartAIManaSet.generated.h"


/**
 * 
 */
UCLASS()
class SMARTAI_API USmartAIManaSet : public USmartAIAttributeSetBase
{
	GENERATED_BODY()

public:
	USmartAIManaSet();
	
	ATTRIBUTE_ACCESSORS(USmartAIManaSet, Mana);
	ATTRIBUTE_ACCESSORS(USmartAIManaSet, MaxMana);

	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes|Mana|Events")
	FSmartAIAttributeEvent OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes|Mana|Events")
	FSmartAIAttributeEvent OnMaxManaChanged;

protected:
	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const override;

private:
	UPROPERTY(BlueprintReadOnly, Category = "SmartAI|Mana", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, Category = "SmartAI|Mana", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;

	float ManaBeforeAttributeChange;
	float MaxManaBeforeAttributeChange;
	
};
