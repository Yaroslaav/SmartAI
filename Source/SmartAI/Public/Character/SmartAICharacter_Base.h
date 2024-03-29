// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/AttributeSets/SmartAIAttributeSetBase.h"
#include "GameFramework/Character.h"
#include "SmartAICharacter_Base.generated.h"

UCLASS()
class SMARTAI_API ASmartAICharacter_Base : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>  AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<USmartAIAttributeSetBase> AttributeSet;

public:	
	ASmartAICharacter_Base();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	USmartAIAttributeSetBase* GetAttributeSet() const { return AttributeSet; }
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
