// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/SmartAIAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "SmartAICharacterWithAbilities.generated.h"

UCLASS()
class SMARTAI_API ASmartAICharacterWithAbilities : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:	
	ASmartAICharacterWithAbilities();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Components",meta = (AllowPrivateAccess ="true" ))
	TObjectPtr<USmartAIAbilitySystemComponent>  AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "GAS|Attributes|AttributeSet",meta = (AllowPrivateAccess ="true" ))
	TObjectPtr<const class USmartAIHealthSet> HealthAttributeSet;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "GAS|Attributes|AttributeSet",meta = (AllowPrivateAccess ="true" ))
	TObjectPtr<const class USmartAIManaSet> ManaAttributeSet;


};
