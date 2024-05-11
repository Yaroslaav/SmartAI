// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmartAICharacterWithAbilities.h"

#include "AbilitySystemComponent.h"
#include "Character/Abilities/AttributeSets/SmartAIHealthSet.h"
#include "Character/Abilities/AttributeSets/SmartAIManaSet.h"
// Sets default values
ASmartAICharacterWithAbilities::ASmartAICharacterWithAbilities()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<USmartAIAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

UAbilitySystemComponent* ASmartAICharacterWithAbilities::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASmartAICharacterWithAbilities::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AbilitySystemComponent->RefreshAbilityActorInfo();
}

void ASmartAICharacterWithAbilities::UnPossessed()
{
	Super::UnPossessed();
	AbilitySystemComponent->RefreshAbilityActorInfo();
}

void ASmartAICharacterWithAbilities::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	HealthAttributeSet = AbilitySystemComponent->GetSet<USmartAIHealthSet>();
	ManaAttributeSet = AbilitySystemComponent->GetSet<USmartAIManaSet>();
	//UE_LOG( LogTemp, Warning, TEXT("SmartAICharacterWithAbilities BeginPlay: Mana attribute"));
}	