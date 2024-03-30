// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmartAICharacterWithAbilities.h"

#include "AbilitySystemComponent.h"
#include "Character/Abilities/AttributeSets/SmartAIHealthSet.h"
#include "Character/Abilities/AttributeSets/SmartAIManaSet.h"
// Sets default values
ASmartAICharacterWithAbilities::ASmartAICharacterWithAbilities()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	//HealthAttributeSet = CreateDefaultSubobject<USmartAIHealthSet>(TEXT("HealthAttributeSet"));
}

UAbilitySystemComponent* ASmartAICharacterWithAbilities::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ASmartAICharacterWithAbilities::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	HealthAttributeSet = AbilitySystemComponent->GetSet<USmartAIHealthSet>();
	ManaAttributeSet = AbilitySystemComponent->GetSet<USmartAIManaSet>();
	UE_LOG( LogTemp, Warning, TEXT("SmartAICharacterWithAbilities BeginPlay: Mana attribute"));
	//ManaAttributeSet = CreateDefaultSubobject<USmartAIManaSet>(TEXT("ManaAttributeSet"));
}	

// Called every frame
void ASmartAICharacterWithAbilities::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASmartAICharacterWithAbilities::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

