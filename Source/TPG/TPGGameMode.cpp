// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPGGameMode.h"
#include "Static/MapManager.h"
#include "Blueprint/UserWidget.h"
#include "Public/MainUI.h"

ATPGGameMode::ATPGGameMode()
{
	Score = 0;
}

void ATPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("TPGGameMode BeginPlay Triggered"));
	MapManager::Initialize();

	if (HUDUIClass)
	{
		HUDUIInstance = CreateWidget<UUserWidget>(GetWorld(), HUDUIClass);
		if (HUDUIInstance)
		{
			HUDUIInstance->AddToViewport();
		}
	}
}
	
void ATPGGameMode::AddScore(int32 scoreToAdd)
{
	Score += scoreToAdd;
	if (HUDUIInstance)
	{
		Cast<UMainUI>(HUDUIInstance)->SetScore(Score);
	}
}