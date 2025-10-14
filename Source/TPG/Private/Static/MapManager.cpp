// Fill out your copyright notice in the Description page of Project Settings.


#include "Static/MapManager.h"

MapManager::MapManager()
{
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

MapManager::~MapManager()
{
}

void MapManager::SpawnNextRoom(ARoom* CurrentRoom)
{
	//ARoom NewRoom = 
	FVector CurrentExit = CurrentRoom->GetExitLocation();
}