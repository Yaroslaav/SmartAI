// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SmartAI/Messages/SmartAIVerbMessage_AnimNotify.h"
#include "AnimNotify_SendGameplayEvent.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API UAnimNotify_SendGameplayEvent : public UAnimNotify
{
	GENERATED_BODY()
public:

	UAnimNotify_SendGameplayEvent();
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(ExposeOnSpawn = true))
	FGameplayTag MessageTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnimNotify", meta=(ExposeOnSpawn = true))
	FGameplayEventData Payload;
};
