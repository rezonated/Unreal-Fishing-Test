// Vanan Andreas - 2024


#include "UserWidget/MeterBar/UserWidgetMeterBar_CastMeterBar.h"

#include "FishingFeatureUI.h"
#include "FishingTags.h"
#include "GameplayTagContainer.h"
#include "Components/ProgressBar.h"
#include "Curves/CurveLinearColor.h"
#include "Engine/Engine.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"

void UUserWidgetMeterBar_CastMeterBar::NativeConstruct()
{
	Super::NativeConstruct();

	FishingMessageListenerAsync =	 UVAGameplayMessaging_ListenForGameplayMessages::ListenForGameplayMessagesViaChannel(this, FFishingTags::Get().Messaging_Fishing_UI_Cast_Update);
	
	FishingMessageListenerAsync->OnGameplayMessageReceived.AddUniqueDynamic(this, &ThisClass::OnFishingMessageReceived);

	FishingMessageListenerAsync->Activate();
}

void UUserWidgetMeterBar_CastMeterBar::NativeDestruct()
{
	if (FishingMessageListenerAsync)
	{
		FishingMessageListenerAsync->Cancel();
	}

	Super::NativeDestruct();
}

FLinearColor UUserWidgetMeterBar_CastMeterBar::GetColorForProgress(const float& InProgress,
	const FLinearColor& DefaultColor) const
{
	if (!CastMeterBarColorCurve)
	{
		UE_LOG(LogFishingFeatureUI, Warning, TEXT("CastMeterBarColorCurve is not set! Please make sure to set it in the details panel. Returning default color."));
		return DefaultColor;
	}

	return CastMeterBarColorCurve->GetLinearColorValue(InProgress);
}

void UUserWidgetMeterBar_CastMeterBar::SetProgressBarColor(const FLinearColor& InColor) const
{
	if (!ProgressBar_MeterBar)
	{
		UE_LOG(LogFishingFeatureUI, Warning, TEXT("MeterBar is not set! Please make sure to name it ProgressBar_MeterBar in the details panel. Returning."));
		return;
	}

	ProgressBar_MeterBar->SetFillColorAndOpacity(InColor);

}

void UUserWidgetMeterBar_CastMeterBar::OnFishingMessageReceived(const FGameplayTag& Channel,
	const FVAAnyUnreal& MessagePayload)
{
	const bool bPayloadIsFloat = MessagePayload.Is<float>();
	if (!bPayloadIsFloat)
	{
		UE_LOG(LogFishingFeatureUI, Warning, TEXT("Expected payload for fishing is not a float! Ignoring message."));
		return;
	}
	
	const float Progress = MessagePayload.Get<float>();
	const FLinearColor Color = GetColorForProgress(Progress);
	
	SetProgress(Progress);
	SetProgressBarColor(Color);
}
