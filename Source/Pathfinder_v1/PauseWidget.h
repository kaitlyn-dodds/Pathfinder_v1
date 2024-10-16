// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PauseWidget.generated.h"

class APathfinderPlayerController;

/**
 * 
 */
UCLASS()
class PATHFINDER_V1_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	APathfinderPlayerController* PlayerController;

	APathfinderPlayerController* GetPlayerController();

protected:

	UFUNCTION(BlueprintCallable)
	void OnResumeBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnRestartBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnExitToMainMenuBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnExitBtnClicked();

public:
	
	virtual void NativeConstruct() override;

};
