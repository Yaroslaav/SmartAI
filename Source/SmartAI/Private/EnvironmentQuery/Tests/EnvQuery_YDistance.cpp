// Fill out your copyright notice in the Description page of Project Settings.

#include "EnvironmentQuery/Tests/EnvQuery_YDistance.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"


UEnvQuery_YDistance::UEnvQuery_YDistance()
{
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UEnvQuery_YDistance::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UE_LOG(LogEQS, Warning, TEXT("-----------------------------------"));
	UE_LOG(LogEQS, Warning, TEXT("YDistance Test was runned"));
	UObject* Owner = QueryInstance.Owner.Get();
	if(!Owner)
	{
		UE_LOG(LogEQS, Error, TEXT("Failed to get owner"));
		return;
	}
	
	FloatValueMin.BindData(Owner, QueryInstance.QueryID);
	float MinDist = FloatValueMin.GetValue();
	FloatValueMax.BindData(Owner, QueryInstance.QueryID);
	float MaxDist = FloatValueMax.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		float Score = 1;
		FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());
		
		FHitResult HitResult;
		FVector Start = FVector(ItemLocation.X, ItemLocation.Y, ItemLocation.Z - MinDist);
		FVector End = FVector(Start.X, Start.Y, Start.Z - MaxDist);
		
		UE_LOG(LogEQS, Warning, TEXT("-----------------------------------"));
		UE_LOG(LogEQS, Warning, TEXT("Spawn Trace %d"), It.GetIndex());
		
		if(GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, FCollisionQueryParams(), FCollisionResponseParams()))
		{
			UE_LOG(LogEQS, Warning, TEXT("Item Index: %d"), It.GetIndex());
			UE_LOG(LogEQS, Warning, TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName());
		}
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 5.0f);

		
		UE_LOG(LogEQS, Warning, TEXT("Score: %f"), Score);
		It.SetScore(TestPurpose, FilterType, Score, MinDist, MaxDist);
	}
}
