// Fill out your copyright notice in the Description page of Project Settings.



#include "PathfinderPlayerController.h"
#include "PauseWidget.h"

void APathfinderPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = true;

}

void APathfinderPlayerController::PauseGame()
{
	// check if game is already paused
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		// remove from viewport
		if (PauseWidget)
		{
			PauseWidget->RemoveFromParent();
		}

		// set input mode
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);

		// hide mouse btn
		bShowMouseCursor = false;
		

		// unpause game
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		
	}
	else
	{
		// pause game
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// create pause menu widget
		if (PauseWidgetClass)
		{
			if (PauseWidget == nullptr) {
				PauseWidget = CreateWidget<UPauseWidget>(this, PauseWidgetClass);
			}
			
			// set input mode to UI only
			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputMode);

			// show mouse cursor
			bShowMouseCursor = true;

			// add to viewport 
			PauseWidget->AddToViewport(0);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Unable to create pause widget"));
		}
	}
}

void APathfinderPlayerController::RestartGame()
{
	FString MapName = GetWorld()->GetMapName();
	MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	UGameplayStatics::OpenLevel(
		GetWorld(), 
		FName(MapName),
		true, 
		""
	);
}

void APathfinderPlayerController::ExitToMainMenu()
{
	// load MainMenu level 
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu", false, "");
}

void APathfinderPlayerController::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, false);
}