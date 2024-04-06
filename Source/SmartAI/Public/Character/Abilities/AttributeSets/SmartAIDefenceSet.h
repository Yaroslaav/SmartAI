// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Abilities/AttributeSets/SmartAIAttributeSetBase.h"
#include "AbilitySystemComponent.h"
#include "SmartAIDefenceSet.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API USmartAIDefenceSet : public USmartAIAttributeSetBase
{
	GENERATED_BODY()
public:
	USmartAIDefenceSet();
	
	ATTRIBUTE_ACCESSORS(USmartAIDefenceSet, DefencePercent);

protected:
	UFUNCTION()
	void OnRep_DefencePercent(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DefencePercent, Category = "SmartAI|Defence", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData DefencePercent;

	float DefencePercentBeforeAttributeChange;
};
