// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttributeSet.h"
#include "SmartAIAttributeSetBase.generated.h"

class AActor;
class UObject;
class UWorld;
struct FGameplayEffectSpec;


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FSmartAIAttributeEvent, AActor*, EffectInstigator, AActor*, EffectCauser, const FGameplayEffectSpec&, EffectSpec, float, EffectMagnitude, float, OldValue, float, NewValue);/**
 * 
 */
UCLASS()
class SMARTAI_API USmartAIAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	USmartAIAttributeSetBase();
	
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

	UFUNCTION()
	UWorld* GetWorld() const override;

};
