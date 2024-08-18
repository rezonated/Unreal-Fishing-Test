// Vanan Andreas - 2024


#include "GameStateBase/GameStateBase_StairwayFishingGame.h"

#include "FishingTags.h"
#include "StairwayFishingGameCore.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"

void AGameStateBase_StairwayFishingGame::SetCurrentFishingGameLoopState(const EFishingGameLoopState& InFishingGameLoopState)
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

	UVAGameplayMessaging_ListenForGameplayMessages* ListenForGameplayMessages = UVAGameplayMessaging_ListenForGameplayMessages::ListenForGameplayMessagesViaChannel(this, FFishingTags::Get().Messaging_GameState_StateChange);

	ListenForGameplayMessages->OnGameplayMessageReceived.AddUniqueDynamic(this, &ThisClass::OnGameStateChangeMessageReceived);

	ListenForGameplayMessages->Activate();
}

void AGameStateBase_StairwayFishingGame::OnGameStateChangeMessageReceived(const FGameplayTag& Channel,
	const FVAAnyUnreal&                                                                       MessagePayload)
{
	if (!MessagePayload.Is<uint8>())
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Message Payload is not a valid EFishingGameLoopState, won't continue..."));
		return;
	}

	const uint8 FishingGameLoopState = MessagePayload.Get<uint8>();

	const EFishingGameLoopState FishingGameLoopStateAsEnum = static_cast<EFishingGameLoopState>(FishingGameLoopState);

	SetCurrentFishingGameLoopState(FishingGameLoopStateAsEnum);
}