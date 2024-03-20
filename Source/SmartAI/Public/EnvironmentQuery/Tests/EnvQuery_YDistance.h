// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQuery_YDistance.generated.h"
/**
 * 
 */
UCLASS()
class SMARTAI_API UEnvQuery_YDistance : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UEnvQuery_YDistance();
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
