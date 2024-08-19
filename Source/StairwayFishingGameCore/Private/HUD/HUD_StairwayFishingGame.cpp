// Vanan Andreas - 2024


#include "HUD/HUD_StairwayFishingGame.h"

#include "Blueprint/UserWidget.h"

void AHUD_StairwayFishingGame::SetupMainOverlayWidget()
{
	if (!MainOverlayWidgetClass.Get())
	{
		UE_LOG(LogTemp, Warning, TEXT("MainOverlayWidgetClass is not valid, please make sure you have a valid UserWidget class set in details tab!"));

		return;
	}

	MainOverlayWidget = CreateWidget<UUserWidget>(GetWorld(), MainOverlayWidgetClass);

	MainOverlayWidget->AddToViewport();
}

void AHUD_StairwayFishingGame::BeginPlay()
{
	Super::BeginPlay();

	SetupMainOverlayWidget();
}