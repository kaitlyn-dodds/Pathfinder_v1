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
	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = true;
	CameraBoom->bInheritRoll = false;

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

	// Set target location to starting position
	TargetLocation = GetActorLocation();
	
}

// Called every frame
void APathfinderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If Character not at target location
	if (TargetLocation != FVector::ZeroVector && !TargetLocation.Equals(GetActorLocation(), 0.0001f))
	{
		//UE_LOG(LogTemp, Display, TEXT("Not at target, moving..."));

		//UE_LOG(LogTemp, Display, TEXT("Target: %s"), *TargetLocation.ToString());
		//UE_LOG(LogTemp, Display, TEXT("Actor: %s"), *GetActorLocation().ToString());
		
		FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();

		AddMovementInput(Direction);

		FRotator NewRotation = Direction.Rotation();
		FRotator CurrentRotation = GetActorRotation();

		SetActorRotation(FRotator(CurrentRotation.Pitch, NewRotation.Yaw, CurrentRotation.Roll));
	}
}

// Called to bind functionality to input
void APathfinderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// bind input actions
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Mouse Click
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Triggered, this, &APathfinderCharacter::MouseClick);

	}
}

void APathfinderCharacter::MouseClick(const FInputActionValue& Value)
{
	if (PlayerController)
	{
		// Capture mouse down location
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

			UE_LOG(LogTemp, Display, TEXT("Updating target location"));
			TargetLocation = HitResults.ImpactPoint;
		}
	}
}
