// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentQuery/Tests/EQTest_ABCAngle.h"

#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"

FLinearColor CalculateGradientColor(float GradientValue)
{
	FLinearColor StartColor = FLinearColor::Red;
	FLinearColor EndColor = FLinearColor::Green;

	return FMath::Lerp(StartColor, EndColor, GradientValue);
}

UEQTest_ABCAngle::UEQTest_ABCAngle()
{
	Point1 = UEnvQueryContext_Querier::StaticClass();
	Point2 = UEnvQueryContext_Querier::StaticClass();
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UEQTest_ABCAngle::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UE_LOG(LogEQS, Warning, TEXT("--------UEQTest_DistFromPointToVector--------"));
	UObject* Owner = QueryInstance.Owner.Get();
	if(!Owner)
	{
		UE_LOG(LogEQS, Error, TEXT("Failed to get owner"));
		return;
	}
	UE_LOG(LogEQS, Warning, TEXT("Owner - %s"), *Owner->GetName());
	
	FloatValueMin.BindData(Owner, QueryInstance.QueryID);
	float MinDist = FloatValueMin.GetValue();
	FloatValueMax.BindData(Owner, QueryInstance.QueryID);
	float MaxDist = FloatValueMax.GetValue();

	FloatPendingAngle.BindData( Owner, QueryInstance.QueryID );
	float PendingAngle = FloatPendingAngle.GetValue();

	if(PointsRole.Num() != 3)
	{
		return;
	}
	TArray<FVector> ContextLocations;
	if (!QueryInstance.PrepareContext(Point1, ContextLocations))
	{
		return;
	}
	if (!QueryInstance.PrepareContext(Point2, ContextLocations))
	{
		return;
	}
	if( PendingAngle > 180)
	{
		if(static_cast<int>(PendingAngle) / 180 % 2 != 0)
		{
			PendingAngle = 180 - static_cast<int>(PendingAngle) % 180;
		}else
		{
			PendingAngle = static_cast<int>(PendingAngle) % 180;
			PendingAngle = PendingAngle == 0 ? .5f : PendingAngle;
		}
	}
	
	UE_LOG( LogEQS, Warning, TEXT("PendingAngle - %f"), PendingAngle);
		

	for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		FVector PointA = PointsRole[A] > -1 ? ContextLocations[PointsRole[A]] : GetItemLocation(QueryInstance, It.GetIndex());
		FVector PointB = PointsRole[B] > -1 ? ContextLocations[PointsRole[B]] : GetItemLocation(QueryInstance, It.GetIndex());
		FVector PointC = PointsRole[C] > -1 ? ContextLocations[PointsRole[C]] : GetItemLocation(QueryInstance, It.GetIndex());
		
		FVector AB = PointB - PointA;
		FVector BC = PointC - PointB;

		float DotAB_BC = FVector::DotProduct(AB, BC);

		float LengthAB = AB.Size();
		float LengthBC = BC.Size();

		float CosineAngle = DotAB_BC / (LengthAB * LengthBC);

		float AngleABC = FMath::RadiansToDegrees(FMath::Acos(CosineAngle));
		
		float res = 1 - FMath::Abs(180 - PendingAngle - AngleABC) / PendingAngle;
		DrawDebugLine(GetWorld(), PointA, PointB,  CalculateGradientColor(res).ToFColor(true), false, 20.0f, 0, 5.0f);
		DrawDebugLine(GetWorld(), PointB, PointC,CalculateGradientColor(res).ToFColor(true), false, 20.0f, 0, 5.0f);
		if(TestPurpose == EEnvTestPurpose::Score)
		{
			//Distance -= MinDistance;
		}
		UE_LOG( LogEQS, Warning, TEXT("Angle: %f, Result: %f"), AngleABC, res);
		It.SetScore(TestPurpose, FilterType, res, MinDist, MaxDist);
	}

}
