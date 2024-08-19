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


void AGameModeBase_StairwayFishingGame::OnFishingGameLoopStateChanged(const FGameplayTag& FishingGameLoopState)
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
	
	const bool bShouldFish = FishingGameLoopState.MatchesTag(FFishingTags::Get().FishingGameLoopState_Fishing);

	TogglePlayerControllerMode(PlayerController, bShouldFish);

	TriggerScreenFadeInOut(PlayerCameraManager, FishingGameLoopState, TransitionFadeInTime, TransitionFadeOutTime, PossessedPawnAsSwitchableFishingView);
}

void AGameModeBase_StairwayFishingGame::TriggerScreenFadeInOut(APlayerCameraManager* InPlayerCameraManager, const FGameplayTag& InFishingGameLoopState, const float& TransitionFadeInTime, const float& TransitionFadeOutTime, ISwitchableFishingViewInterface* InSwitchableFishingView) const
{
	FTimerHandle TimerHandle;
	
	InPlayerCameraManager->StartCameraFade(0.f, 1.f, TransitionFadeInTime, FLinearColor::Black, true, true);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [InPlayerCameraManager, TransitionFadeOutTime, this, InFishingGameLoopState, InSwitchableFishingView] {
		InSwitchableFishingView->SetFishingView(InFishingGameLoopState);
		UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_GameMode_StateChangeFinish, InFishingGameLoopState);
		InPlayerCameraManager->StartCameraFade(1.f, 0.f, TransitionFadeOutTime, FLinearColor::Black, true, true);
	}, TransitionFadeInTime, false);
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

void AGameModeBase_StairwayFishingGame::TogglePlayerControllerMode(APlayerController* InPlayerController, const bool& bIsEnabled) const
{
	if (!InPlayerController)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("InPlayerController is not valid, have you actually pass the correct pointer? Won't continue initializing..."));
		return;
	}

	InPlayerController->EnableInput(InPlayerController);
	
	if (!bIsEnabled)
	{
		InPlayerController->SetInputMode(FInputModeUIOnly());
	}
	else
	{
		InPlayerController->SetInputMode(FInputModeGameOnly());
	}

	InPlayerController->SetShowMouseCursor(!bIsEnabled);
}

void AGameModeBase_StairwayFishingGame::InitialFadeIn()
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

	PlayerCameraManager->StartCameraFade(1.f, 0.f, GameModeTransitionConfigAsset->GetGameModeTransitionConfig().InitialGameModeTransitionTime, FLinearColor::Black, true, true);
}

void AGameModeBase_StairwayFishingGame::BeginPlay()
{
	Super::BeginPlay();

	ListenForGameLoopStateChanges();

	InitialFadeIn();
}
