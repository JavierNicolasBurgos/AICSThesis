// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIOverviewThesisGameMode.h"
#include "AIOverviewThesisCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAIOverviewThesisGameMode::AAIOverviewThesisGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
