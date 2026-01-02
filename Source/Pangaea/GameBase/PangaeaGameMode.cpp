// Copyright Epic Games, Inc. All Rights Reserved.

#include "PangaeaGameMode.h"
#include "../Player/PangaeaPlayerController.h"
#include "../Player/PangaeaCharacter.h"
#include "UObject/ConstructorHelpers.h"

APangaeaGameMode::APangaeaGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APangaeaPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/Player/BP_PlayerCharacter.BP_PlayerCharacter_C"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/Player/BP_TopDownPlayerController.BP_TopDownPlayerController_C"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}