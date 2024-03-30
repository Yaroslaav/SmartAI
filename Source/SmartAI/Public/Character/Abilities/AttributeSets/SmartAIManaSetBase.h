// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "Character/Abilities/AttributeSets/SmartAIAttributeSetBase.h"
#include "SmartAIManaSetBase.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API USmartAIManaSetBase : public USmartAIAttributeSetBase
{
	GENERATED_BODY()
public:
	USmartAIManaSetBase();
	
	ATTRIBUTE_ACCESSORS(USmartAIManaSetBase, Mana);
	ATTRIBUTE_ACCESSORS(USmartAIManaSetBase, MaxMana);
	ATTRIBUTE_ACCESSORS(USmartAIManaSetBase, StealMana);
	ATTRIBUTE_ACCESSORS(USmartAIManaSetBase, RegenMana);
	
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes|Mana|Events")
	FSmartAIAttributeEvent OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes|Mana|Events")
	FSmartAIAttributeEvent OnMaxManaChanged;
protected:
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "SmartAI|Mana", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "SmartAI|Mana", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, Category="SmartAI|Mana", Meta=(AllowPrivateAccess=true))
	FGameplayAttributeData RegenMana;

	UPROPERTY(BlueprintReadOnly, Category="SmartAI|Mana", Meta=(HideFromModifiers, AllowPrivateAccess=true))
	FGameplayAttributeData StealMana;

	float ManaBeforeAttributeChange;
	float MaxManaBeforeAttributeChange;

};