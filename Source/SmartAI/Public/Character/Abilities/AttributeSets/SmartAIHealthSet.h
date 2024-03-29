// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "Character/Abilities/AttributeSets/SmartAIAttributeSetBase.h"
#include "SmartAIHealthSet.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API USmartAIHealthSet : public USmartAIAttributeSetBase
{
	GENERATED_BODY()

public:
	USmartAIHealthSet();

	ATTRIBUTE_ACCESSORS(USmartAIHealthSet, Health);
	ATTRIBUTE_ACCESSORS(USmartAIHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(USmartAIHealthSet, Healing);
	ATTRIBUTE_ACCESSORS(USmartAIHealthSet, Damage);

	mutable FSmartAIAttributeEvent OnHealthChanged;

	mutable FSmartAIAttributeEvent OnMaxHealthChanged;

	mutable FSmartAIAttributeEvent OnOutOfHealth;

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "SmartAI|Health", Meta = (HideFromModifiers, AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "SmartAI|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	bool bOutOfHealth;

	float MaxHealthBeforeAttributeChange;
	float HealthBeforeAttributeChange;

	UPROPERTY(BlueprintReadOnly, Category="SmartAI|Health", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Healing;

	UPROPERTY(BlueprintReadOnly, Category="SmartAI|Health", Meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData Damage;

};




