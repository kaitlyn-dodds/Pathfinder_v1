// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pathfinder_v1GameMode.h"
#include "Pathfinder_v1Character.h"
#include "UObject/ConstructorHelpers.h"

APathfinder_v1GameMode::APathfinder_v1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
