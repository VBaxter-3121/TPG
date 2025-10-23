// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

void UMainUI::SetScore(int32 newScore)
{
	ScoreDisplay->SetText(FText::AsNumber(newScore));
}