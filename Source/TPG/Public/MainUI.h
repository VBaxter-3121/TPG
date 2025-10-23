// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class TPG_API UMainUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Function to update the text
	UFUNCTION(BlueprintCallable)
	void SetScore(int32 newScore);

protected:
	// Bind to the TextBlock in your WBP
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreDisplay;
};
