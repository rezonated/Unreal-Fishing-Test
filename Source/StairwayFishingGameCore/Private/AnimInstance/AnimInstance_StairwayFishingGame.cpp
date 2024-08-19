// Vanan Andreas - 2024


#include "AnimInstance/AnimInstance_StairwayFishingGame.h"

#include "FishingTags.h"
#include "StairwayFishingGameCore.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"

void UAnimInstance_StairwayFishingGame::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	StateTag = FFishingTags::Get().AnimInstance_Fishing_State_Idling;

	StateChangeMessageListenerAsync = UVAGameplayMessaging_ListenForGameplayMessages::ListenForGameplayMessagesViaChannel(this, FFishingTags::Get().Messaging_Fishing_AnimInstance_StateChange);

	StateChangeMessageListenerAsync->OnGameplayMessageReceived.AddUniqueDynamic(this, &ThisClass::OnStateChangeMessageReceived);

	StateChangeMessageListenerAsync->Activate();
}

void UAnimInstance_StairwayFishingGame::BeginDestroy()
{
	if (IsValid(StateChangeMessageListenerAsync))
	{
		StateChangeMessageListenerAsync->Cancel();
		StateChangeMessageListenerAsync = nullptr;
	}
	
	Super::BeginDestroy();
}

void UAnimInstance_StairwayFishingGame::OnStateChangeMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload)
{
	const bool bPayloadIsGameplayTag = MessagePayload.Is<FGameplayTag>();
	if (!bPayloadIsGameplayTag)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Message Payload is not a Gameplay Tag, won't continue..."));
		return;
	}

	const FGameplayTag& ReceivedStateTag = MessagePayload.Get<FGameplayTag>();

	StateTag = ReceivedStateTag;

	StateTagChanged();
}

void UAnimInstance_StairwayFishingGame::StateTagChanged()
{
	UAnimMontage* MontageToPlay = TagToMontageMap.FindChecked(StateTag);

	Montage_Play(MontageToPlay, 1.f);
}