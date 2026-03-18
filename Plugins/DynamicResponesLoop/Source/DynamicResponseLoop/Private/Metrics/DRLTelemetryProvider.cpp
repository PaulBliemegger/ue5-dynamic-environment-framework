// Fill out your copyright notice in the Description page of Project Settings.


#include "Metrics/DRLTelemetryProvider.h"
#include "Async/Async.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UDRLTelemetryProvider::InitializeSession(const UDRLWorldStateConfig* Config)
{
	if (!Config || !Config->bEnableTelemetry) 
	{
		CurrentSessionFile = "";
		UE_LOG(LogTemp, Warning, TEXT("DRLTelemetryProvider: Telemetry disabled, no session file will be created."));
		return;
	}

	CurrentRunID = FDateTime::Now().ToString();
	FString SafeID = CurrentRunID.Replace(TEXT(":"), TEXT("-")).Replace(TEXT("."), TEXT("-"));
    
	// Creates a unique file for this specific play session
	CurrentSessionFile = FPaths::ProjectSavedDir() + TEXT("DRL_Telemetry/Run_") + SafeID + TEXT(".csv");
	
	UE_LOG(LogTemp, Log, TEXT("DRLTelemetryProvider: Initialized new telemetry session with file: %s"), *CurrentSessionFile);
}

void UDRLTelemetryProvider::LogActionAsync(const UDRLWorldStateConfig* Config, const FActionRecord& Record)
{
	if (!Config || !Config->bEnableTelemetry || !Config->bEnableLiveHeartbeat || CurrentSessionFile.IsEmpty()) return;

	FString CSVLine = FString::Printf(TEXT("%s,%.2f,%s,%.2f,,, %d,\n"),
		*CurrentRunID, Record.Timestamp, *Record.ActionTag.ToString(), Record.Intensity, Config->bIsControlGroup ? 1 : 0);

	SaveCSVLineInternalAsync(CurrentSessionFile, CSVLine);
}

void UDRLTelemetryProvider::LogSummaryAsync(const UDRLWorldStateConfig* Config, const FRunMetrics& Metrics, const FGameplayTagContainer& FinalState)
{
	if (!Config || !Config->bEnableTelemetry || CurrentSessionFile.IsEmpty()) return;

	FString SummaryLine = FString::Printf(TEXT("%s,SUMMARY,---,---,%.4f,%.2f,%d,\"%s\"\n"),
		*CurrentRunID, Metrics.ActionEntropy, Metrics.Duration, 
		Config->bIsControlGroup ? 1 : 0, *FinalState.ToStringSimple());

	SaveCSVLineInternalAsync(CurrentSessionFile, SummaryLine);
}

void UDRLTelemetryProvider::SaveCSVLineInternalAsync(const FString& FilePath, const FString& Line)
{
	// Capture variables by value [=] for thread safety
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [FilePath, Line]()
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        
		// Ensure folder exists
		FString Dir = FPaths::GetPath(FilePath);
		if (!PlatformFile.DirectoryExists(*Dir)) PlatformFile.CreateDirectory(*Dir);

		FString FinalOutput = Line;
		if (!PlatformFile.FileExists(*FilePath))
		{
			// Column Headers
			FinalOutput = TEXT("RunID,Timestamp,ActionTag,Intensity,Entropy,Duration,IsControl,WorldState\n") + Line;
		}

		FFileHelper::SaveStringToFile(FinalOutput, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
	});
}

void UDRLTelemetryProvider::ExportRunToCSV(const FString& RunID, const TArray<FActionRecord>& History, const FGameplayTagContainer& FinalWorldState, const FRunMetrics& Metrics, bool bIsControlGroup)
{
	FString FilePath = FPaths::ProjectSavedDir() + TEXT("DRL_Telemetry/Thesis_Results.csv");
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Prepare Header with New Columns
	FString CSVContent = "";
	if (!PlatformFile.FileExists(*FilePath)) {
		CSVContent += TEXT("RunID,Duration,TotalActions,Entropy,IsControl,WorldState\n");
	}

	// We write ONE summary row per run for easy Excel/Python plotting
	CSVContent += FString::Printf(TEXT("%s,%.2f,%d,%.4f,%d,\"%s\"\n"),
		*RunID,
		Metrics.Duration,
		Metrics.TotalActions,
		Metrics.ActionEntropy,
		bIsControlGroup ? 1 : 0,
		*FinalWorldState.ToStringSimple());

	FFileHelper::SaveStringToFile(CSVContent, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}