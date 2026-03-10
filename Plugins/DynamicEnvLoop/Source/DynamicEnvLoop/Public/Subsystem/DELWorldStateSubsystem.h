// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Types/DELTypes.h"
#include "DELWorldStateConfig.h"
#include "DELWorldStateSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionLoggedSignature, FActionRecord, LoggedRecord);

/**
 * 
 */
UCLASS()
class DYNAMICENVLOOP_API UDELWorldStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "DEL|Events")
	FOnActionLoggedSignature OnActionLogged;
	
	// Step 1: Called by Player/Companions during the Dungeon phase
	UFUNCTION(BlueprintCallable, Category = "DEL|Observer")
	void LogAction(FGameplayTag ActionTag, float Intensity = 1.0f);

	// Step 2 & 3: Triggered when returning to the Hub area
	UFUNCTION(BlueprintCallable, Category = "DEL|Brain")
	void UpdateWorldState();

	UFUNCTION(BlueprintCallable, Category = "DEL|Config")
	void SetActiveConfig(UDELWorldStateConfig* NewConfig);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEL|State")
	TArray<FActionRecord> CurrentRunHistory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DEL|State")
	FGameplayTagContainer CurrentWorldState;

	UPROPERTY(Transient)
	TObjectPtr<UDELWorldStateConfig> ActiveConfig;

	// We instantiate the Evaluator classes here so they can hold state if needed
	UPROPERTY(Transient)
	TArray<TObjectPtr<UDELWorldStateEvaluator>> InstancedEvaluators;
};
