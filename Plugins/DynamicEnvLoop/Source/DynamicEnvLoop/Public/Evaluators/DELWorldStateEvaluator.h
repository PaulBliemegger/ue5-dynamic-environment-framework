// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "Types/DELTypes.h"
#include "DELWorldStateEvaluator.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew)
class DYNAMICENVLOOP_API UDELWorldStateEvaluator : public UObject
{
	GENERATED_BODY()

public:
	// Takes the run history and modifies the World State appropriately
	UFUNCTION(BlueprintNativeEvent, Category = "DEL|Evaluation")
	void Evaluate(const TArray<FActionRecord>& History, UPARAM(ref) FGameplayTagContainer& InOutWorldState);
    
	virtual void Evaluate_Implementation(const TArray<FActionRecord>& History, FGameplayTagContainer& InOutWorldState)
	{
		// Default C++ implementation (override in child C++ classes or Blueprints)
	}
};
