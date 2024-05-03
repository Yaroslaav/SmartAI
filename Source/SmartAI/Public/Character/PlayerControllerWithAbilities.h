// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "SmartAICharacterWithAbilities.h"
#include "Abilities/SmartAIAbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerWithAbilities.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API APlayerControllerWithAbilities : public APlayerController, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	APlayerControllerWithAbilities();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(Blueprintable, meta = (AllowPrivateAccess ="true" ))
	ASmartAICharacterWithAbilities* GetCurrentOwningPlayerCharacter();
	
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS|Components",meta = (AllowPrivateAccess ="true" ))
	ASmartAICharacterWithAbilities* CurrentOwningPlayerCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Components",meta = (AllowPrivateAccess ="true" ))
	TObjectPtr<USmartAIAbilitySystemComponent>  AbilitySystemComponent;

};
