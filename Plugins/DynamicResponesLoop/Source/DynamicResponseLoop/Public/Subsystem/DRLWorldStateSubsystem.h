// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "Types/DRLTypes.h"
#include "UDRLWorldStateConfig.h"
#include "DRLWorldStateSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActionLoggedSignature, FActionRecord, LoggedRecord);

/**
 * 
 */
UCLASS()
class DYNAMICRESPONSELOOP_API UDRLWorldStateSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "DEL|Events")
	FOnActionLoggedSignature OnActionLogged;
	
	// Step 1: Called by Player/Companions during the Dungeon phase
	UFUNCTION(BlueprintCallable, Category = "DRL|Observer")
	void LogAction(FGameplayTag ActionTag, float Intensity = 1.0f);

	// Step 2 & 3: Triggered when returning to the Hub area
	UFUNCTION(BlueprintCallable, Category = "DRL|Brain")
	void UpdateWorldState();

	UFUNCTION(BlueprintCallable, Category = "DRL|Config")
	void SetActiveConfig(UDRLWorldStateConfig* NewConfig);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DRL|State")
	TArray<FActionRecord> CurrentRunHistory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DRL|State")
	FGameplayTagContainer CurrentWorldState;

	UPROPERTY(Transient)
	TObjectPtr<UDRLWorldStateConfig> ActiveConfig;

	// We instantiate the Evaluator classes here so they can hold state if needed
	UPROPERTY(Transient)
	TArray<TObjectPtr<UDRLWorldStateEvaluator>> InstancedEvaluators;
};