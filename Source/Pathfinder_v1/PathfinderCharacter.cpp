// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfinderCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APathfinderCharacter::APathfinderCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup and attach camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 400.f);
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 0.f);
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Setup and attach camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom);
	// FollowCamera->bUsePawnControlRotation = false;  // dont rotate the camera 
	FollowCamera->SetWorldRotation(FRotator(0.f, -35.f, 0.f));

}

// Called when the game starts or when spawned
void APathfinderCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APathfinderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APathfinderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

