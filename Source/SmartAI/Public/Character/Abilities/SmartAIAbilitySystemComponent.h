// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SmartAIAbilitySystemComponent.generated.h"


class UInputAction;

USTRUCT()
struct FAbilityInputBinding
{
	GENERATED_BODY()

	int32  InputID = 0;
	uint32 OnPressedHandle = 0;
	uint32 OnReleasedHandle = 0;
	TArray<FGameplayAbilitySpecHandle> BoundAbilitiesStack;
};

/**
 * 
 */
UCLASS()
class SMARTAI_API USmartAIAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	USmartAIAbilitySystemComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void LevelUpAbility(FGameplayAbilitySpecHandle AbilityHandle, int32 LevelMagnitude);
	
	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void SetInputBinding(UInputAction* InputAction, FGameplayAbilitySpecHandle AbilityHandle);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearInputBinding(FGameplayAbilitySpecHandle AbilityHandle);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Input Abilities")
	void ClearAbilityBindings(UInputAction* InputAction);

private:
	void OnAbilityInputPressed(UInputAction* InputAction);

	void OnAbilityInputReleased(UInputAction* InputAction);

	void RemoveEntry(UInputAction* InputAction);

	void TryBindAbilityInput(UInputAction* InputAction, FAbilityInputBinding& AbilityInputBinding);

	FGameplayAbilitySpec* FindAbilitySpec(FGameplayAbilitySpecHandle Handle);

	virtual void BeginPlay() override;

	UPROPERTY(transient)
	TMap<UInputAction*, FAbilityInputBinding> MappedAbilities;

	UPROPERTY(transient)
	UEnhancedInputComponent* InputComponent;
};
