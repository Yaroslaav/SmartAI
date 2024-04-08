 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EQTest_DistFromPointToVector.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API UEQTest_DistFromPointToVector : public UEnvQueryTest
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category=Distance)
	TSubclassOf<UEnvQueryContext> LonePoint;
	
	UPROPERTY(EditDefaultsOnly, Category=Distance)
	TSubclassOf<UEnvQueryContext> VectorStart;

	UPROPERTY(EditDefaultsOnly, Category=Distance)
	FAIDataProviderFloatValue FloatMinDistance;
	
public:
	UEQTest_DistFromPointToVector();
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
