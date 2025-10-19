// Fill out your copyright notice in the Description page of Project Settings.


#include "Static/MapManager.h"

// This line is required to set the memory that will be used for these static variables
TArray<TSubclassOf<ARoom>> MapManager::RoomPool;
TArray<FString> MapManager::RoomPaths;

void MapManager::Initialize()
{
	UE_LOG(LogTemp, Display, TEXT("MapManager Initializing"));
	// FPaths::ProjectContentDir() gets the file path of the project's content folder
	FString FilePath = FPaths::ProjectContentDir() + "/TxtFiles/RoomPaths.txt";
	FString FileContent;

	// Loads the contents of the file at FilePath to FileContent
	if (FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		FileContent.ParseIntoArrayLines(RoomPaths, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load RoomPaths.txt"));
	}

	// const means the variable is read only, using & means the variable can be rebound to each string in RoomPaths
	for (const FString& Path : RoomPaths)
	{
		// This appends "_C" to each file path, needed to access the generated class rather than the asset
		FString FullPath = Path + TEXT("_C");
		// Two possible options for loading the class
		// Using StaticLoadObject is more versatile (cast it to the type expected)
		// Using StaticLoadClass removes the need to cast the object, but of course only if it is a class
		// UClass* LoadedClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *FullPath));
		UClass* LoadedClass = StaticLoadClass(ARoom::StaticClass(), nullptr, *FullPath);

		if (LoadedClass && LoadedClass->IsChildOf(ARoom::StaticClass()))
		{
			RoomPool.Add(LoadedClass);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load class at path %s"), *FullPath)
		}
	}
}

void MapManager::SpawnNextRoom(UWorld* WorldContext, ARoom* CurrentRoom)
{
	if (!WorldContext || !CurrentRoom || RoomPool.Num() == 0)
	{
		return;
	}

	FVector CurrentExitPosition = CurrentRoom->GetExitLocation();
	FRotator CurrentExitRotation = CurrentRoom->GetExitRotation();
	int32 RandomIndex = FMath::RandRange(0, RoomPool.Num() - 1);

	FActorSpawnParameters SpawnParams;
	// First spawn new room as TemporaryEditorActor to calculate position
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ARoom* NewRoom = WorldContext->SpawnActor<ARoom>(RoomPool[RandomIndex], FVector::ZeroVector, CurrentExitRotation, SpawnParams);

	FVector Offset = NewRoom->GetEntranceLocation() - NewRoom->GetRoomLocation();

	NewRoom->SetActorLocation(CurrentExitPosition - Offset);
}