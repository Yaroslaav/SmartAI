// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SmartAIVerbMessage.h"

#include "SmartAIVerbMessage_AnimNotify.generated.h"

// Represents a generic message of the form Instigator Verb Target (in Context, with Magnitude)
USTRUCT(BlueprintType)
struct FSmartAIVerbMessage_AnimNotify : public FSmartAIVerbMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category=Gameplay)
	UAnimMontage *AnimMontage;
};
