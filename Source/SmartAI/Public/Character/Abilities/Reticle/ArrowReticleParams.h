// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityWorldReticle.h"
#include "ArrowReticleParams.generated.h"

USTRUCT(BlueprintType)
struct SMARTAI_API FArrowReticleParams : public FWorldReticleParameters
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category=Reticle)
	float MinArrowLength = 100.0f;
};
