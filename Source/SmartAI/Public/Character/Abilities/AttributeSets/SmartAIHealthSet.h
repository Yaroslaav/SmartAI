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

	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes|Health|Events")
	FSmartAIAttributeEvent OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes|Health|Events")
	mutable FSmartAIAttributeEvent OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "Gas|Attributes|Health|Events")
	mutable FSmartAIAttributeEvent OnOutOfHealth;

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;


private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "SmartAI|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "SmartAI|Health", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	bool bOutOfHealth;
	
	float HealthBeforeAttributeChange;
	float MaxHealthBeforeAttributeChange;

};




