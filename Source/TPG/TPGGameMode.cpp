// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPGGameMode.h"
#include "Static/MapManager.h"

ATPGGameMode::ATPGGameMode()
{
	// stub
}

void ATPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("TPGGameMode BeginPlay Triggered"));
	MapManager::Initialize();
}