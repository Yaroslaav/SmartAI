// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/Notifies/AnimNotify_SendGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"

UAnimNotify_SendGameplayEvent::UAnimNotify_SendGameplayEvent()
{
}

void UAnimNotify_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, *MeshComp->GetOwner()->GetName());
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), MessageTag, Payload);

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Custom AnimNotify triggered!"));
	//}
}

