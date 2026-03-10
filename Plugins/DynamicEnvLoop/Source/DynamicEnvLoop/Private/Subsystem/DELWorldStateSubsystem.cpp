// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystem/DELWorldStateSubsystem.h"
#include "Engine/World.h"

void UDELWorldStateSubsystem::SetActiveConfig(UDELWorldStateConfig* NewConfig)
{
	ActiveConfig = NewConfig;
	if (ActiveConfig)
	{
		CurrentWorldState = ActiveConfig->DefaultWorldState;
        
		// Instantiate evaluators from the provided subclasses
		InstancedEvaluators.Empty();
		for (TSubclassOf<UDELWorldStateEvaluator> EvalClass : ActiveConfig->Evaluators)
		{
			if (EvalClass)
			{
				UDELWorldStateEvaluator* NewEval = NewObject<UDELWorldStateEvaluator>(this, EvalClass);
				InstancedEvaluators.Add(NewEval);
			}
		}
	}
}

void UDELWorldStateSubsystem::LogAction(FGameplayTag ActionTag, float Intensity)
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

void UDELWorldStateSubsystem::UpdateWorldState()
{
	if (!ActiveConfig) return;

	// Step 2 & 3: Run the Data Transformation via Evaluators
	for (UDELWorldStateEvaluator* Evaluator : InstancedEvaluators)
	{
		if (Evaluator)
		{
			Evaluator->Evaluate(CurrentRunHistory, CurrentWorldState);
		}
	}

	// Note: If bIsControlGroup is true, we will skip broadcasting the delegate here in Phase 4.
	// Telemetry export (Phase 5) should be called directly after this loop.
}