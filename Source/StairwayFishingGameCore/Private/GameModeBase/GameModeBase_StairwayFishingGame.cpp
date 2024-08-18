// Vanan Andreas - 2024


#include "GameModeBase/GameModeBase_StairwayFishingGame.h"

#include "FishingTags.h"
#include "StairwayFishingGameCore.h"
#include "DataAsset/DataAsset_GameModeTransitionConfig.h"
#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"
#include "GameStateBase/GameStateBase_StairwayFishingGame.h"
#include "Interface/SwitchableFishingViewInterface.h"


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

	if (!GameModeTransitionConfigAsset)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("GameModeTransitionConfigAsset is not valid, have you set it up correctly in the game mode? Won't continue initializing..."));
		return;
	}

	APawn* PossessedPawn = PlayerController->GetPawn();
	if (!PossessedPawn)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("PossessedPawn is not valid, this is not supposed to happen. Won't continue initializing..."));
		return;
	}

	const bool bIsPossessedPawnImplementsSwitchableFishingView = PossessedPawn->Implements<USwitchableFishingViewInterface>();
	if (!bIsPossessedPawnImplementsSwitchableFishingView)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("PossessedPawn does not implement ISwitchableFishingViewInterface, won't continue initializing..."));
		return;
	}

	ISwitchableFishingViewInterface* PossessedPawnAsSwitchableFishingView = Cast<ISwitchableFishingViewInterface>(PossessedPawn);
	if (!PossessedPawnAsSwitchableFishingView)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("PossessedPawnAsSwitchableFishingView is not valid, have you set it up correctly in the game mode? Won't continue initializing..."));
		return;
	}

	const float TransitionFadeInTime = GameModeTransitionConfigAsset->GetGameModeTransitionConfig().TransitionFadeInTime;
	const float TransitionFadeOutTime = GameModeTransitionConfigAsset->GetGameModeTransitionConfig().TransitionFadeOutTime;

	FTimerHandle TimerHandle;

	uint8 Payload = static_cast<uint8>(FishingGameLoopState);

	switch (FishingGameLoopState)
	{
		case EFishingGameLoopState::Fishing:
			PlayerController->EnableInput(PlayerController);
			PlayerController->SetInputMode(FInputModeGameOnly());

			PlayerCameraManager->StartCameraFade(1.f, 0.f, TransitionFadeInTime, FLinearColor::Black, true, true);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerCameraManager, TransitionFadeOutTime, this, Payload, PossessedPawnAsSwitchableFishingView, FishingGameLoopState] {
				PossessedPawnAsSwitchableFishingView->SetFishingView(FishingGameLoopState);

				UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_GameMode_StateChangeFinish, Payload);

				PlayerCameraManager->StartCameraFade(0.f, 1.f, TransitionFadeOutTime, FLinearColor::Black, true, true);
			}, TransitionFadeInTime, false);

			break;
		case EFishingGameLoopState::ShowFish:
			PlayerController->DisableInput(PlayerController);
			PlayerController->SetInputMode(FInputModeUIOnly());

			PlayerCameraManager->StartCameraFade(0.f, 1.f, TransitionFadeInTime, FLinearColor::Black, true, true);

			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [PlayerCameraManager, TransitionFadeOutTime, this, Payload, PossessedPawnAsSwitchableFishingView, FishingGameLoopState] {
				PossessedPawnAsSwitchableFishingView->SetFishingView(FishingGameLoopState);

				UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_GameMode_StateChangeFinish, Payload);

				PlayerCameraManager->StartCameraFade(1.f, 0.f, TransitionFadeOutTime, FLinearColor::Black, true, true);

			}, TransitionFadeInTime, false);

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

	if (!GameModeTransitionConfigAsset)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("GameModeTransitionConfigAsset is not valid, have you set it up correctly in the game mode? Won't continue initializing..."));
		return;
	}

	PlayerCameraManager->StartCameraFade(1.f, 0.f, GameModeTransitionConfigAsset->GetGameModeTransitionConfig().InitialGameModeTransitionTime, FLinearColor::Black, true, true);
}