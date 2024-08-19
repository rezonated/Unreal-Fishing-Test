// Vanan Andreas - 2024


#include "GameStateBase/GameStateBase_StairwayFishingGame.h"

#include "FishingTags.h"
#include "StairwayFishingGameCore.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"

void AGameStateBase_StairwayFishingGame::SetCurrentFishingGameLoopState(
	const FGameplayTag& InFishingGameLoopState)
{
	if (CurrentFishingGameLoopState == InFishingGameLoopState)
	{
		return;
	}

	CurrentFishingGameLoopState = InFishingGameLoopState;

	OnFishingGameLoopStateChanged.Broadcast(CurrentFishingGameLoopState);
}

void AGameStateBase_StairwayFishingGame::BeginPlay()
{
	Super::BeginPlay();

	GameStateChangeMessageListenerAsync = UVAGameplayMessaging_ListenForGameplayMessages::ListenForGameplayMessagesViaChannel(this, FFishingTags::Get().Messaging_GameState_StateChange);

	GameStateChangeMessageListenerAsync->OnGameplayMessageReceived.AddUniqueDynamic(
		this, &ThisClass::OnGameStateChangeMessageReceived);

	GameStateChangeMessageListenerAsync->Activate();
}

void AGameStateBase_StairwayFishingGame::CleanupGameStateChangeMessageListener()
{
	if (IsValid(GameStateChangeMessageListenerAsync))
	{
		GameStateChangeMessageListenerAsync->Cancel();
		GameStateChangeMessageListenerAsync = nullptr;
	}
}

void AGameStateBase_StairwayFishingGame::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CleanupGameStateChangeMessageListener();
	
	Super::EndPlay(EndPlayReason);
}

void AGameStateBase_StairwayFishingGame::OnGameStateChangeMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload)
{
	if (!MessagePayload.Is<FGameplayTag>())
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Message Payload is not a valid Gameplay Tag, won't continue..."));
		return;
	}

	const FGameplayTag FishingGameLoopState = MessagePayload.Get<FGameplayTag>();
	if (!FishingGameLoopState.IsValid())
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Message Payload is not a valid Gameplay Tag, won't continue..."));
		return;
	}

	SetCurrentFishingGameLoopState(FishingGameLoopState);
}
