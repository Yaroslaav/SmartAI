// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavModifierVolume.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "NavModifierVolume_Base.generated.h"

UCLASS()
class SMARTAI_API ANavModifierVolume_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANavModifierVolume_Base();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NavMesh|Components",meta = (AllowPrivateAccess ="true" ))
	TObjectPtr<UBoxComponent> BoxComponentPtr = CreateDefaultSubobject<UBoxComponent>(TEXT("NavModVolume"));
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
