// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentQuery/Tests/EnvQueryTest_TraceWithOffset.h"

#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"

UEnvQueryTest_TraceWithOffset::UEnvQueryTest_TraceWithOffset()
{
	TraceTo = UEnvQueryContext_Querier::StaticClass();
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UEnvQueryTest_TraceWithOffset::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UE_LOG(LogEQS, Warning, TEXT("--------UEnvQueryTest_TraceWithOffset--------"));

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

	FloatStartPointZOffset.BindData(Owner, QueryInstance.QueryID);
	float StartPointZOffset = FloatStartPointZOffset.GetValue();
	
	FloatEndPointZOffset.BindData(Owner, QueryInstance.QueryID);
	float EndPointZOffset = FloatEndPointZOffset.GetValue();
	TArray<FVector> ContextLocations;
	
	if (!QueryInstance.PrepareContext(TraceTo, ContextLocations))
	{
		return;
	}
	FCollisionResponseParams ResponseParam;
	ResponseParam.CollisionResponse.Camera = ECR_Ignore;
	ResponseParam.CollisionResponse.Pawn = ECR_Ignore;
	
	for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		float Score = 1;
		FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());
		FHitResult HitResult;

		FVector Start = FVector(ItemLocation.X, ItemLocation.Y, ItemLocation.Z + StartPointZOffset);
		FVector End = FVector(ContextLocations[0].X, ContextLocations[0].Y, ContextLocations[0].Z + EndPointZOffset);

		UE_LOG(LogEQS, Warning, TEXT("-----------------------------------"));
		UE_LOG(LogEQS, Warning, TEXT("Spawn Trace %d"), It.GetIndex());
		
		if(GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, FCollisionQueryParams(), ResponseParam))
		{
			UE_LOG(LogEQS, Warning, TEXT("Item Index: %d"), It.GetIndex());
			UE_LOG(LogEQS, Warning, TEXT("Hit object name: %s"), *HitResult.GetActor()->GetName());
			Score = 0;
		}
		//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 5.0f);
		
		UE_LOG(LogEQS, Warning, TEXT("Score: %f"), Score);
		It.SetScore(TestPurpose, FilterType, Score, MinDist, MaxDist);
	}
}

FText UEnvQueryTest_TraceWithOffset::GetDescriptionTitle() const
{
	return Super::GetDescriptionTitle();
}

FText UEnvQueryTest_TraceWithOffset::GetDescriptionDetails() const
{
	return Super::GetDescriptionDetails();
}
