// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/VAAnyUnreal.h"
#include "UserWidget_FishingDoneScreen.generated.h"

class UVAGameplayMessaging_ListenForGameplayMessages;
class UUserWidget_Button;
/**
 * Fishing done screen widget for the game. Contains the box container for buttons for restarting and quitting the game. 
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidget_FishingDoneScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	/*
	 * Forces the construction of the widget to collapse the button container upon pre-construction of the widget.
	 */
	virtual void NativePreConstruct() override;

	/*
	 * Forces the construction of the widget to collapse the button container upon construction of the widget.
	 */
	virtual void NativeConstruct() override;

	/*
	 * Actual cleaning up of the game mode finish change state listener.
	 */
	void CleanupGameModeFinishChangeStateListener();

	/*
	 * Trigger cleaning up of the game mode finish change state listener.
	 */
	virtual void NativeDestruct() override;

	/*
	 * Toggles the visibility of the button container.
	 */
	void ToggleWidgetButtonsContainerVisibility(bool bIsVisible = false) const;

	/*
	 * Handles the game mode finish change state message.
	 */
	UFUNCTION()
	void OnFishingGameLoopStateChanged(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	/*
	 * Current button container for the fishing done screen.
	 */
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UWidget* Widget_ButtonsContainer = nullptr;

	/*
	 * Cached game mode finish change state message listener.
	 */
	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* GameModeFinishChangeStateMessageListenerAsync = nullptr;
};