// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartAIAssetManager.h"
#include "AbilitySystemGlobals.h"
void USmartAIAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("Hello World, StartInitialLoading"))
}
