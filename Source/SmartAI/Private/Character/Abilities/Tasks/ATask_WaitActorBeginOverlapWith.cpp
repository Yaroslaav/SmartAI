// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Abilities/Tasks/ATask_WaitActorBeginOverlapWith.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ATask_WaitActorBeginOverlapWith)


UATask_WaitActorBeginOverlapWith* UATask_WaitActorBeginOverlapWith::WaitActorBeginOverlapWith(UGameplayAbility* OwningAbility, AActor* InTargetActor, AActor* InActorToOverlapWith, bool InCallOnce)
{
	UATask_WaitActorBeginOverlapWith* MyObj = NewAbilityTask<UATask_WaitActorBeginOverlapWith>(OwningAbility);
	MyObj->TargetActor = InTargetActor;
	MyObj->ActorToOverlapWith = InActorToOverlapWith;
	MyObj-> CallOnce = InCallOnce;
	return MyObj;
}


void UATask_WaitActorBeginOverlapWith::Activate()
{
	if( IsValid( this->TargetActor ) && IsValid( this->ActorToOverlapWith ) )
	{
		this->TargetActor->OnActorBeginOverlap.AddDynamic(this, &UATask_WaitActorBeginOverlapWith::OnBeginOverlap);
	}
}

void UATask_WaitActorBeginOverlapWith::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor != this->ActorToOverlapWith )
	{
		return;
	}
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		this->OnOverlapBegin.Broadcast();
		if(this->CallOnce)
		{
			EndTask();
		}
	}
}
void UATask_WaitActorBeginOverlapWith::OnDestroy(bool AbilityEnded)
{
	if( IsValid( this->TargetActor ) && IsValid( this->ActorToOverlapWith ) )
	{
		this->TargetActor->OnActorBeginOverlap.RemoveDynamic(this, &UATask_WaitActorBeginOverlapWith::OnBeginOverlap);
	}
	Super::OnDestroy(AbilityEnded);
}