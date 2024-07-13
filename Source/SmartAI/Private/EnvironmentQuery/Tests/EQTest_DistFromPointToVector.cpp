// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentQuery/Tests/EQTest_DistFromPointToVector.h"

#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"
UEQTest_DistFromPointToVector::UEQTest_DistFromPointToVector()
{
	Point1 = UEnvQueryContext_Querier::StaticClass();
	Point2 = UEnvQueryContext_Querier::StaticClass();
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();

}

void UEQTest_DistFromPointToVector::RunTest(FEnvQueryInstance& QueryInstance) const
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

	FloatMinDistance.BindData( Owner, QueryInstance.QueryID );
	float MinDistance = FloatMinDistance.GetValue();

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

	for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		FVector LonePointLocation = PointsRole[LonePoint] > -1 ? ContextLocations[PointsRole[LonePoint]] : GetItemLocation(QueryInstance, It.GetIndex());
		FVector VectorStartLocation = PointsRole[VectorStart] > -1 ? ContextLocations[PointsRole[VectorStart]] : GetItemLocation(QueryInstance, It.GetIndex());
		FVector VectorEndLocation = PointsRole[VectorEnd] > -1 ? ContextLocations[PointsRole[VectorEnd]] : GetItemLocation(QueryInstance, It.GetIndex());

		FVector LineDirection = (VectorEndLocation - VectorStartLocation).GetSafeNormal();
		FVector ClosestPointOnLine;
		float Distance = FMath::PointDistToLine(LonePointLocation, LineDirection, VectorStartLocation, ClosestPointOnLine);



		DrawDebugLine(GetWorld(), ClosestPointOnLine, LonePointLocation, FColor::Red, false, 20.0f, 0, 5.0f);
		DrawDebugLine(GetWorld(), VectorStartLocation, VectorEndLocation, FColor::Orange, false, 20.0f, 0, 5.0f);

		if(TestPurpose == EEnvTestPurpose::Score)
		{
			//Distance -= MinDistance;
		}
		It.SetScore(TestPurpose, FilterType, Distance, MinDist, MaxDist);
	}
}
