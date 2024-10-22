// Fill out your copyright notice in the Description page of Project Settings.


#include "PathfinderCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PathfinderPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

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

}

// Called when the game starts or when spawned
void APathfinderCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Find and set Player Controller
	PlayerController = Cast<APathfinderPlayerController>(GetController());

	// Setup Input Mapping Context
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PathfinderMappingContext, 0);
		}
	}

	if (FollowCamera)
	{
		FollowCamera->SetWorldRotation(FRotator(-35.f, 0.f, 0.f));
	}
	
}

// Called every frame
void APathfinderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (PlayerController)
	{
		FHitResult HitResults;
		PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false, 
			HitResults
		);

		if (HitResults.bBlockingHit)
		{
			DrawDebugSphere(
				GetWorld(),
				HitResults.ImpactPoint,
				10.f,
				12,
				FColor::Blue,
				true,
				0.f
			);

			if (CameraBoom)
			{
				UE_LOG(LogTemp, Display, TEXT("Trying to move camera boom: %s"), *HitResults.ImpactPoint.ToString());
				FVector CurrentLocation = CameraBoom->GetComponentLocation();
				FVector TargetLocation = FVector(HitResults.ImpactPoint.X, HitResults.ImpactPoint.Y, 0.0);

				FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, 100);
				
				CameraBoom->SetWorldLocation(NewLocation);
			}

		}
	}*/

}

// Called to bind functionality to input
void APathfinderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// bind input actions
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Mouse Click
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Completed, this, &APathfinderCharacter::MouseClick);

	}
}

void APathfinderCharacter::MouseClick(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Click click click"));
}
