// Copyright Epic Games, Inc. All Rights Reserved.

#include "PerceptionGameMode.h"
#include "PerceptionCharacter.h"
#include "UObject/ConstructorHelpers.h"

APerceptionGameMode::APerceptionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
