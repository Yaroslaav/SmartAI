// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentQuery/Tests/EQTest_DistFromPointToVector.h"

#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"

UEQTest_DistFromPointToVector::UEQTest_DistFromPointToVector()
{
	LonePoint = UEnvQueryContext_Querier::StaticClass();
	VectorStart = UEnvQueryContext_Querier::StaticClass();
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

	TArray<FVector> ContextLocations;
	if (!QueryInstance.PrepareContext(LonePoint, ContextLocations))
	{
		return;
	}
	FVector LonePointLocation = ContextLocations[0];
	if (!QueryInstance.PrepareContext(VectorStart, ContextLocations))
	{
		return;
	}
	FVector VectorStartLocation = ContextLocations[1];
	//int i = 0;
	for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());
		FVector LineDirection = (ItemLocation - VectorStartLocation).GetSafeNormal();
		FVector ClosestPointOnLine;
		float Distance = FMath::PointDistToLine(LonePointLocation, LineDirection, VectorStartLocation, ClosestPointOnLine);
		/*if(i == 0)
		{
			DrawDebugLine(GetWorld(), ClosestPointOnLine, LonePointLocation, FColor::Red, false, 20.0f, 0, 5.0f);
			DrawDebugLine(GetWorld(), VectorStartLocation, ItemLocation, FColor::Orange, false, 20.0f, 0, 5.0f);
		}
		i++;*/
		if(TestPurpose == EEnvTestPurpose::Score)
		{
			//Distance -= MinDistance;
		}
		It.SetScore(TestPurpose, FilterType, Distance, MinDist, MaxDist);
	}
}
