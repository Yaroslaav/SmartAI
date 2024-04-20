// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ATask_WaitActorBeginOverlapWith.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitForActorBeginOverlapWithDelegate);

class AActor;
/**
 * 
 */
UCLASS()
class SMARTAI_API UATask_WaitActorBeginOverlapWith : public UAbilityTask
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintAssignable)
	FWaitForActorBeginOverlapWithDelegate OnOverlapBegin;

	virtual void Activate() override;

	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UATask_WaitActorBeginOverlapWith* WaitActorBeginOverlapWith( UGameplayAbility* OwningAbility ,AActor* InTargetActor, AActor* InActorToOverlapWith, bool CallOnce = false );

	AActor* TargetActor;
	AActor* ActorToOverlapWith;
	bool CallOnce;
protected:

	virtual void OnDestroy(bool AbilityEnded) override;

};
