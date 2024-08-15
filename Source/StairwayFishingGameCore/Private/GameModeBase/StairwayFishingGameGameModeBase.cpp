// Vanan Andreas - 2024


#include "GameModeBase/StairwayFishingGameGameModeBase.h"

#include "Pawn/StairwayFishingGamePawn.h"
#include "PlayerController/StairwayFishingGamePlayerController.h"

AStairwayFishingGameGameModeBase::AStairwayFishingGameGameModeBase()
{
	static ConstructorHelpers::FClassFinder<AStairwayFishingGamePawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Pawn/BP_StairwayFishingGamePawn"));
	
	if (PlayerPawnClassFinder.Class)
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}

	static ConstructorHelpers::FClassFinder<AStairwayFishingGamePlayerController> PlayerControllerClassFinder(TEXT("/Game/Blueprints/PlayerController/BP_StairwayFishingGamePlayerController"));

	if (PlayerControllerClassFinder.Class)
	{
		PlayerControllerClass = PlayerControllerClassFinder.Class;
	}
}
