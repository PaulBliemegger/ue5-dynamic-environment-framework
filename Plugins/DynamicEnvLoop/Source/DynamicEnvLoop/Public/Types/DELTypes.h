#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DELTypes.generated.h"

USTRUCT(BlueprintType)
struct DYNAMICENVLOOP_API FActionRecord
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEL|Action")
	FGameplayTag ActionTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEL|Action")
	float Timestamp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DEL|Action")
	float Intensity = 1.0f;
};