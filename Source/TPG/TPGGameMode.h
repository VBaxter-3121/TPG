// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPGGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ATPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	ATPGGameMode();

protected:
	virtual void BeginPlay() override;

private:
	int32 Score;

public:
	UFUNCTION()
	void AddScore(int32 scoreToAdd);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDUIClass;

	UPROPERTY()
	UUserWidget* HUDUIInstance;
};



