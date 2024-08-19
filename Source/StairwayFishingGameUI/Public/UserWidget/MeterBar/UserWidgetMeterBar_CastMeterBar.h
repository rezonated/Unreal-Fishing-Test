// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Runtime/VAAnyUnreal.h"
#include "UserWidget/UserWidget_MeterBar.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"
#include "UserWidgetMeterBar_CastMeterBar.generated.h"

class UCurveLinearColor;
/**
 * Cast meter bar widget to represent how long the player has held LMB.
 * Progress bar color is determined by the color curve and listens from the game for the cast update message.
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidgetMeterBar_CastMeterBar : public UUserWidget_MeterBar
{
	GENERATED_BODY()

protected:
	/*
	 * Listens for the cast update message and initializes the meter bar.
	 */
	void ListenForUICastUpdateMessage();

	/*
	 * Initializes the meter bar default values.
	 */
	void InitializeMeterBar();

	/*
	 * Listens for the cast update message and updates the progress bar color and progress.
	 */
	virtual void NativeConstruct() override;

	/*
	 * Actual cleanup the cast update message listener.
	 */
	void CleanupUICastUpdateListener();

	/*
	 * Triggers the cleanup of the cast update message listener.
	 */
	virtual void NativeDestruct() override;

	/*
	 * Gets the color for the progress based on the progress value to the color curve.
	 */
	FLinearColor GetColorForProgress(const float& InProgress, const FLinearColor& DefaultColor = FLinearColor::White) const;

	/*
	 * Sets the color of the progress bar.
	 */
	void SetProgressBarColor(const FLinearColor& InColor) const;

	/*
	 * Color curve for the cast meter bar.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Cast Meter Bar")
	UCurveLinearColor* CastMeterBarColorCurve = nullptr;

private:
	/*
	 * Handles the cast update message.
	 */
	UFUNCTION()
	void OnFishingMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	/*
	 * Cached cast update message listener async.
	 */
	UPROPERTY()
	UVAGameplayMessaging_ListenForGameplayMessages* FishingMessageListenerAsync = nullptr;
};