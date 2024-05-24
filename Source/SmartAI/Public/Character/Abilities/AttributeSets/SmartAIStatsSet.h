// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SmartAIAttributeSetBase.h"
#include "SmartAIStatsSet.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API USmartAIStatsSet : public USmartAIAttributeSetBase
{
	GENERATED_BODY()
	
public:
	USmartAIStatsSet();

	ATTRIBUTE_ACCESSORS(USmartAIStatsSet, AutoAttackSpeedBonus);
	ATTRIBUTE_ACCESSORS(USmartAIStatsSet, CooldownRate);
	ATTRIBUTE_ACCESSORS(USmartAIStatsSet, DamageBonus);

	
	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const override;

private:
	UPROPERTY(BlueprintReadOnly, Category = "SmartAI|AutoAttackSpeedBonus", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AutoAttackSpeedBonus;
	UPROPERTY(BlueprintReadOnly, Category = "SmartAI|CooldownRate", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CooldownRate;
	UPROPERTY(BlueprintReadOnly, Category = "SmartAI|DamageBonus", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData DamageBonus;
};
