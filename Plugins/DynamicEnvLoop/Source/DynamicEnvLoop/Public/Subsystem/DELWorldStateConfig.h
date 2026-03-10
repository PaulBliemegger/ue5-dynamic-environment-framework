// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Evaluators/DELWorldStateEvaluator.h"
#include "DELWorldStateConfig.generated.h"

UCLASS(BlueprintType)
class DYNAMICENVLOOP_API UDELWorldStateConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// If true, system logs data but does NOT update the World State or fire delegates
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DRL|Config")
	bool bIsControlGroup = false;

	// The logic modules to run during the Resolution Phase
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DRL|Config")
	TArray<TSubclassOf<UDELWorldStateEvaluator>> Evaluators;

	// Baseline state tags
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DRL|Config")
	FGameplayTagContainer DefaultWorldState;
};