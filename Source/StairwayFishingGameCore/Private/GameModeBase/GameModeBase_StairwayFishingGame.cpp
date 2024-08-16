// Vanan Andreas - 2024


#include "GameModeBase/GameModeBase_StairwayFishingGame.h"

#include "StairwayFishingGameCore.h"
#include "GameStateBase/GameStateBase_StairwayFishingGame.h"


AGameModeBase_StairwayFishingGame::AGameModeBase_StairwayFishingGame()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AGameModeBase_StairwayFishingGame::OnFishingGameLoopStateChanged(const EFishingGameLoopState& FishingGameLoopState)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("PlayerController is not valid, this is not supposed to happen. Won't continue initializing..."));
		return;
	}

	APlayerCameraManager* PlayerCameraManager = PlayerController->PlayerCameraManager;
	if (!PlayerCameraManager)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("PlayerCameraManager is not valid, this is not supposed to happen. Won't continue initializing..."));
		return;
	}

	FTimerHandle TimerHandle;
	
	switch (FishingGameLoopState)
	{
		case EFishingGameLoopState::Fishing:
			PlayerController->EnableInput(PlayerController);
			PlayerController->SetInputMode(FInputModeGameOnly());

			PlayerCameraManager->StartCameraFade(1.f, 0.f, 2.f, FLinearColor::Black, true, true);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerCameraManager]
			{
				PlayerCameraManager->StartCameraFade(0.f, 1.f, 1.f, FLinearColor::Black, true, true);
			}, 2.f, false);
		
			break;
		case EFishingGameLoopState::ShowFish:
			PlayerController->DisableInput(PlayerController);
			PlayerController->SetInputMode(FInputModeUIOnly());

			PlayerCameraManager->StartCameraFade(0.f, 1.f, 2.f, FLinearColor::Black, true, true);
		
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerCameraManager]
			{
				PlayerCameraManager->StartCameraFade(1.f, 0.f, 1.f, FLinearColor::Black, true, true);
			}, 2.f, false);

			break;
	}
}

void AGameModeBase_StairwayFishingGame::ListenForGameLoopStateChanges()
{
	if (!GameState)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("GameState is not valid, this should never happen. Won't continue initializing..."));
		return;
	}

	AGameStateBase_StairwayFishingGame* GameStateStairwayFishingGame = Cast<AGameStateBase_StairwayFishingGame>(GameState);

	if (!GameStateStairwayFishingGame)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("GameStateStairwayFishingGame is not valid, have you set it up correctly in the game mode? Won't continue initializing..."));
		return;
	}

	GameStateStairwayFishingGame->OnFishingGameLoopStateChanged.AddUObject(this, &AGameModeBase_StairwayFishingGame::OnFishingGameLoopStateChanged);
}

void AGameModeBase_StairwayFishingGame::BeginPlay()
{
	Super::BeginPlay();
	
	ListenForGameLoopStateChanges();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("PlayerController is not valid, this is not supposed to happen. Won't continue initializing..."));
		return;
	}

	APlayerCameraManager* PlayerCameraManager = PlayerController->PlayerCameraManager;
	if (!PlayerCameraManager)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("PlayerCameraManager is not valid, this is not supposed to happen. Won't continue initializing..."));
		return;
	}

	PlayerCameraManager->StartCameraFade(1.f, 0.f, .5f, FLinearColor::Black, true, true);
}