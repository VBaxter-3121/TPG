// Copyright Epic Games, Inc. All Rights Reserved.


#include "TPGPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Input/SVirtualJoystick.h"

void ATPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}

	//add to end of AMyFirstPlatformerPlayerController::SetupInputComponent()
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput)
	{
		EnhancedInput->BindAction(PauseAction, ETriggerEvent::Started, this, &ATPGPlayerController::PauseToggle);
	}
}

void ATPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PauseUIClass)
	{
		PauseUIInstance = CreateWidget<UUserWidget>(this, PauseUIClass);
		if (PauseUIInstance)
		{
			PauseUIInstance->AddToViewport();
			PauseUIInstance->SetVisibility(ESlateVisibility::Hidden); // start hidden
		}
	}
}

void ATPGPlayerController::PauseToggle()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Player Controller Pause"));
	}
	if (PauseUIInstance)
	{
		APawn* MyPawn = GetPawn();
		if (PauseUIInstance->GetVisibility() == ESlateVisibility::Visible)
		{
			PauseUIInstance->SetVisibility(ESlateVisibility::Hidden);
			bShowMouseCursor = false;
			SetInputMode(FInputModeGameAndUI());
			if (MyPawn)
			{
				MyPawn->EnableInput(this);
			}
		}
		else
		{
			PauseUIInstance->SetVisibility(ESlateVisibility::Visible);
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
			if (MyPawn)
			{
				MyPawn->DisableInput(this);
			}
		}
	}
}