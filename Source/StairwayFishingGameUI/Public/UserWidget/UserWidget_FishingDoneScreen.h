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
 * 
 */
UCLASS()
class STAIRWAYFISHINGGAMEUI_API UUserWidget_FishingDoneScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	void CleanupGameModeFinishChangeStateListener();

	virtual void NativeDestruct() override;

	void ToggleWidgetButtonsContainerVisibility(bool bIsVisible = false) const;

	UFUNCTION()
	void OnFishingGameLoopStateChanged(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload);

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UWidget* Widget_ButtonsContainer = nullptr;

	UPROPERTY(Transient)
	UVAGameplayMessaging_ListenForGameplayMessages* GameModeFinishChangeStateMessageListenerAsync = nullptr;
};