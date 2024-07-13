// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Tests/EQTest_DistFromPointToVector.h"
#include "EQTest_ABCAngle.generated.h"

/**
 * 
 */
UENUM(Blueprintable)
enum Point
{
	A,
	B,
	C,
};
UCLASS()
class SMARTAI_API UEQTest_ABCAngle : public UEnvQueryTest
{
	GENERATED_BODY()
	/** -1 - item point, 0 - point1, 1 - point2 */
	UPROPERTY(EditDefaultsOnly, Category=Distance, meta = (DisplayName = "Point Role"))
	TMap<TEnumAsByte<Point>, int32> PointsRole;
	
	UPROPERTY(EditDefaultsOnly, Category=Distance)
	TSubclassOf<UEnvQueryContext> Point1;
	
	UPROPERTY(EditDefaultsOnly, Category=Distance)
	TSubclassOf<UEnvQueryContext> Point2;

	UPROPERTY(EditDefaultsOnly, Category=Distance)
	FAIDataProviderFloatValue FloatPendingAngle;
public:
	UEQTest_ABCAngle();
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

};
