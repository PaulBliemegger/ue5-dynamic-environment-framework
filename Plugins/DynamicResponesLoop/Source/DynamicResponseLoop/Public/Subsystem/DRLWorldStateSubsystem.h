// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Types/DRLTypes.h"
#include "UDRLWorldStateConfig.h"
#include "DRLWorldStateSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMICRESPONSELOOP_API UDRLWorldStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	// Step 1: Called by Player/Companions during the Dungeon phase
	UFUNCTION(BlueprintCallable, Category = "DEL|Observer")
	void LogAction(FGameplayTag ActionTag, float Intensity = 1.0f);

	// Step 2 & 3: Triggered when returning to the Hub area
	UFUNCTION(BlueprintCallable, Category = "DEL|Brain")
	void UpdateWorldState();

	UFUNCTION(BlueprintCallable, Category = "DEL|Config")
	void SetActiveConfig(UDRLWorldStateConfig* NewConfig);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEL|State")
	TArray<FActionRecord> CurrentRunHistory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEL|State")
	FGameplayTagContainer CurrentWorldState;

	UPROPERTY(Transient)
	TObjectPtr<UDRLWorldStateConfig> ActiveConfig;

	// We instantiate the Evaluator classes here so they can hold state if needed
	UPROPERTY(Transient)
	TArray<TObjectPtr<UDRLWorldStateEvaluator>> InstancedEvaluators;
};