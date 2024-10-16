// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfinderPlayerController.h"
#include "PauseWidget.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// bind delegates here 
}

void UPauseWidget::OnResumeBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Clicked the resume button!"));
	GetPlayerController()->PauseGame();
}

void UPauseWidget::OnRestartBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Pressed restart"));
}

void UPauseWidget::OnExitToMainMenuBtnClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Pressed Exit to Main Menu"));
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