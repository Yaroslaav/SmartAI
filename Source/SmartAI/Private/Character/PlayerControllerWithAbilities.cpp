// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerControllerWithAbilities.h"

APlayerControllerWithAbilities::APlayerControllerWithAbilities()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<USmartAIAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

UAbilitySystemComponent* APlayerControllerWithAbilities::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

ASmartAICharacterWithAbilities* APlayerControllerWithAbilities::GetCurrentOwningPlayerCharacter()
{
	return CurrentOwningPlayerCharacter;
}

void APlayerControllerWithAbilities::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
