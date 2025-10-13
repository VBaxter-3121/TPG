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
	MapManager();
	~MapManager();
	static void SpawnNextRoom(ARoom* CurrentRoom);

private:
	TArray<TSubclassOf<ARoom>> RoomPool;
};
