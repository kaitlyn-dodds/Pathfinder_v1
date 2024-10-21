// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PathfinderCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PATHFINDER_V1_API APathfinderCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APathfinderCharacter();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* FollowCamera;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
