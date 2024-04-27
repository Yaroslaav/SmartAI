// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SmartAIGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API ASmartAIGameMode : public AGameModeBase
{
	GENERATED_BODY()


	
public:

	ASmartAIGameMode(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, Category=Game)
	bool bPossessPlayerController;

	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;
};
