 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EQTest_DistFromPointToVector.generated.h"

/**
 * 
 */
UENUM(Blueprintable)
enum EPointRole
{
	LonePoint,
	VectorStart,
	VectorEnd,
};
UCLASS()
class SMARTAI_API UEQTest_DistFromPointToVector : public UEnvQueryTest
{
	GENERATED_BODY()
	/** -1 - item point, 0 - point1, 1 - point2 */
	UPROPERTY(EditDefaultsOnly, Category=Distance, meta = (DisplayName = "Point Role"))
	TMap<TEnumAsByte<EPointRole>, int32> PointsRole;
	
	UPROPERTY(EditDefaultsOnly, Category=Distance)
	TSubclassOf<UEnvQueryContext> Point1;
	
	UPROPERTY(EditDefaultsOnly, Category=Distance)
	TSubclassOf<UEnvQueryContext> Point2;

	UPROPERTY(EditDefaultsOnly, Category=Distance)
	FAIDataProviderFloatValue FloatMinDistance;
	
public:
	UEQTest_DistFromPointToVector();
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
