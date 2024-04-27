// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartAIGameMode.h"

ASmartAIGameMode::ASmartAIGameMode(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Smart AI Game Mode: ASmartAIGameMode()"));
	PrimaryActorTick.bCanEverTick = true;
}

void ASmartAIGameMode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	UE_LOG(LogTemp, Warning, TEXT("Smart AI Game Mode: FinishRestartPlayer()"));
	Super::FinishRestartPlayer(NewPlayer, StartRotation);
}
