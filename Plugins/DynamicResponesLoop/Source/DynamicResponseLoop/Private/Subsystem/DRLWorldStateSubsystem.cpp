// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/DRLWorldStateSubsystem.h"
#include "Engine/World.h"

void UDRLWorldStateSubsystem::SetActiveConfig(UDRLWorldStateConfig* NewConfig)
{
	ActiveConfig = NewConfig;
	if (ActiveConfig)
	{
		CurrentWorldState = ActiveConfig->DefaultWorldState;
        
		// Instantiate evaluators from the provided subclasses
		InstancedEvaluators.Empty();
		for (TSubclassOf<UDRLWorldStateEvaluator> EvalClass : ActiveConfig->Evaluators)
		{
			if (EvalClass)
			{
				UDRLWorldStateEvaluator* NewEval = NewObject<UDRLWorldStateEvaluator>(this, EvalClass);
				InstancedEvaluators.Add(NewEval);
			}
		}
	}
	UE_LOG(LogTemp, Log, TEXT("DRLWorldStateSubsystem: Active Config Set - %s"), *GetNameSafe(ActiveConfig));
}

void UDRLWorldStateSubsystem::LogAction(FGameplayTag ActionTag, float Intensity)
{
	if (!ActionTag.IsValid()) return;

	FActionRecord NewRecord;
	NewRecord.ActionTag = ActionTag;
	NewRecord.Intensity = Intensity;
    
	if (UWorld* World = GetWorld())
	{
		NewRecord.Timestamp = World->GetTimeSeconds();
	}

	CurrentRunHistory.Add(NewRecord);
	
	OnActionLogged.Broadcast(NewRecord);
}

void UDRLWorldStateSubsystem::UpdateWorldState()
{
	if (!ActiveConfig) return;
	
	FGameplayTagContainer NewState = CurrentWorldState;

	// Step 2 & 3: Run the Data Transformation via Evaluators
	for (UDRLWorldStateEvaluator* Evaluator : InstancedEvaluators)
	{
		if (Evaluator)
		{
			NewState = Evaluator->Evaluate(CurrentRunHistory, CurrentWorldState);
		}
	}
	
	CurrentWorldState = NewState;
	CurrentRunHistory.Empty();
	
	if (!ActiveConfig->bIsControlGroup)
	{
		OnWorldStateUpdated.Broadcast(CurrentWorldState);
	}
}