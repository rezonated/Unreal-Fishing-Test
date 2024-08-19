// Vanan Andreas - 2024


#include "UserWidget/UserWidget_FishingDoneScreen.h"

#include "FishingTags.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"

void UUserWidget_FishingDoneScreen::NativePreConstruct()
{
	Super::NativePreConstruct();

	ToggleWidgetButtonsContainerVisibility(false);
}

void UUserWidget_FishingDoneScreen::NativeConstruct()
{
	Super::NativeConstruct();

	ToggleWidgetButtonsContainerVisibility(false);

	GameModeFinishChangeStateMessageListenerAsync = UVAGameplayMessaging_ListenForGameplayMessages::ListenForGameplayMessagesViaChannel(this, FFishingTags::Get().Messaging_GameMode_StateChangeFinish);
	GameModeFinishChangeStateMessageListenerAsync->OnGameplayMessageReceived.AddUniqueDynamic(this, &UUserWidget_FishingDoneScreen::OnFishingGameLoopStateChanged);

	GameModeFinishChangeStateMessageListenerAsync->Activate();
}

void UUserWidget_FishingDoneScreen::CleanupGameModeFinishChangeStateListener()
{
	if (IsValid(GameModeFinishChangeStateMessageListenerAsync))
	{
		GameModeFinishChangeStateMessageListenerAsync->Cancel();
		GameModeFinishChangeStateMessageListenerAsync = nullptr;
	}
}

void UUserWidget_FishingDoneScreen::NativeDestruct()
{
	CleanupGameModeFinishChangeStateListener();
	
	Super::NativeDestruct();
}

void UUserWidget_FishingDoneScreen::ToggleWidgetButtonsContainerVisibility(bool bIsVisible) const
{
	 if (!Widget_ButtonsContainer)
	 {
		 UE_LOG(LogTemp, Error, TEXT("Widget_ButtonsContainer is not valid, have you set it up correctly in the Widget Blueprint?"));
		 return;
	 }

	 Widget_ButtonsContainer->SetVisibility(bIsVisible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}

void UUserWidget_FishingDoneScreen::OnFishingGameLoopStateChanged(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload)
{
	const bool bPayloadIsGameplayTag = MessagePayload.Is<FGameplayTag>();
	if (!bPayloadIsGameplayTag)
	{
		UE_LOG(LogTemp, Error, TEXT("MessagePayload is not a gameplay tag, have you broadcasted the correct message? Won't continue..."));
		return;
	}

	const FGameplayTag FishingGameLoopState = MessagePayload.Get<FGameplayTag>();
	if (!FishingGameLoopState.IsValid())
	{
		 UE_LOG(LogTemp, Error, TEXT("FishingGameLoopState tag is not valid, have you broadcasted the correct message? Won't continue..."));
		 return;
	}
	
	const bool bShouldContainerBeVisible = FishingGameLoopState.MatchesTag(FFishingTags::Get().FishingGameLoopState_ShowFish);
	ToggleWidgetButtonsContainerVisibility(bShouldContainerBeVisible);
}
