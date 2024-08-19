// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_StairwayFishingGame.generated.h"

/**
 * General HUD class for the game. Managing the main overlay widget.
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API AHUD_StairwayFishingGame : public AHUD
{
	GENERATED_BODY()

protected:
	/*
	 * Setups the main overlay widget.
	 */
	virtual void BeginPlay() override;

	/*
	 * Actually creates the main overlay widget and adds it to the viewport.
	 */
	void SetupMainOverlayWidget();

	/*
	 * Main overlay widget class to use.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Stairway Fishing Game HUD")
	TSubclassOf<UUserWidget> MainOverlayWidgetClass = nullptr;

	/*
	 * Cached main overlay widget.
	 */
	TWeakObjectPtr<UUserWidget> MainOverlayWidget = nullptr;
};