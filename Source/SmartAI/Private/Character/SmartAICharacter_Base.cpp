// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SmartAICharacter_Base.h"

#include "AbilitySystemComponent.h"
#include "Character/Abilities/AttributeSets/SmartAIAttributeSetBase.h"
#include "Character/Abilities/AttributeSets/SmartAIHealthSet.h"
// Sets default values
ASmartAICharacter_Base::ASmartAICharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<USmartAIHealthSet>(TEXT("HealthAttributeSet"));


}

UAbilitySystemComponent* ASmartAICharacter_Base::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ASmartAICharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->AddSpawnedAttribute(AttributeSet);
}

// Called every frame
void ASmartAICharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASmartAICharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

