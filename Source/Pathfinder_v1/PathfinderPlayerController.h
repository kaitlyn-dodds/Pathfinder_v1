// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PathfinderPlayerController.generated.h"

class UPauseWidget;

/**
 * 
 */
UCLASS()
class PATHFINDER_V1_API APathfinderPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPauseWidget* PauseWidget;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPauseWidget> PauseWidgetClass;

public:

	UFUNCTION(BlueprintCallable)
	void PauseGame();

	UFUNCTION(BlueprintCallable)
	void RestartGame();

	UFUNCTION(BlueprintCallable)
	void ExitToMainMenu();

	UFUNCTION(BlueprintCallable)
	void ExitGame();
	
};
