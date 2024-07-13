// Fill out your copyright notice in the Description page of Project Settings.


#include "NavModifierVolume_Base.h"


// Sets default values
ANavModifierVolume_Base::ANavModifierVolume_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void ANavModifierVolume_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANavModifierVolume_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

