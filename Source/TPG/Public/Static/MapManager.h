// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay_Pieces/room.h"

/**
 * 
 */
class TPG_API MapManager
{
public:
	static void Initialize();
	static void SpawnNextRoom(UWorld* WorldContext, ARoom* CurrentRoom);

private:
	static TArray<TSubclassOf<ARoom>> RoomPool;
	static TArray<FString> RoomPaths;
};
