// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_TraceWithOffset.generated.h"

/**
 * 
 */
UCLASS()
class SMARTAI_API UEnvQueryTest_TraceWithOffset : public UEnvQueryTest
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category=Filter)
	FAIDataProviderFloatValue FloatStartPointZOffset;
	UPROPERTY(EditDefaultsOnly, Category=Filter)
	FAIDataProviderFloatValue FloatEndPointZOffset;

public:
	UEnvQueryTest_TraceWithOffset();
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
	UPROPERTY(EditDefaultsOnly, Category=Trace)
	TSubclassOf<UEnvQueryContext> TraceTo;

};
