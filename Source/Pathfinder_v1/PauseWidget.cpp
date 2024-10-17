// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "PathfinderPlayerController.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// bind delegates here 
}

void UPauseWidget::OnResumeBtnClicked()
{
	GetPlayerController()->PauseGame();
}

void UPauseWidget::OnRestartBtnClicked()
{
	GetPlayerController()->RestartGame();
}

void UPauseWidget::OnExitToMainMenuBtnClicked()
{
	GetPlayerController()->ExitToMainMenu();
}

void UPauseWidget::OnExitBtnClicked()
{
	GetPlayerController()->ExitGame();
}

APathfinderPlayerController* UPauseWidget::GetPlayerController()
{
	if (PlayerController == nullptr)
	{
		PlayerController = Cast<APathfinderPlayerController>(UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0));
	}

	return PlayerController;
}