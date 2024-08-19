// Vanan Andreas - 2024


#include "PlayerController/PlayerController_StairwayFishingGamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StairwayFishingGameCore.h"

void APlayerController_StairwayFishingGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	FSlateApplication::Get().SetAllUserFocusToGameViewport();

	MapInputContext(DefaultInputMappingContext);

	MapInputActions();
}

void APlayerController_StairwayFishingGamePlayerController::MapInputContext(const UInputMappingContext* InMappingContext, const int32& InPriority, const bool& bInClearExistingMappings) const
{
	if (!InMappingContext)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Input Mapping Context is not valid, won't continue mapping input..."));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = nullptr;
	if (!GetEnhancedInputLocalPlayerSubsystem(EnhancedInputLocalPlayerSubsystem))
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Failed to cast Input Component to Enhanced Input Component, please make sure you have the Enhanced Input plugin enabled and that you set InputComponent field to EnhancedInputComponent in project settings!"));
		return;
	}

	if (bInClearExistingMappings)
	{
		EnhancedInputLocalPlayerSubsystem->ClearAllMappings();
	}

	EnhancedInputLocalPlayerSubsystem->AddMappingContext(DefaultInputMappingContext, InPriority);
}

void APlayerController_StairwayFishingGamePlayerController::MapInputActions()
{
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	if (!GetEnhancedInputComponent(EnhancedInputComponent))
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Failed to get Enhanced Input Component, please make sure you have the Enhanced Input plugin enabled and that you set InputComponent field to EnhancedInputComponent in project settings!"));
		return;
	}
	if (!CastingInputAction)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Casting Input Action is not set, please make sure you have a valid Casting Input Action set in details tab!"));
		return;
	}

	EnhancedInputComponent->BindAction(CastingInputAction, ETriggerEvent::Started, this, &ThisClass::OnCastStarted);

	EnhancedInputComponent->BindAction(CastingInputAction, ETriggerEvent::Triggered, this, &ThisClass::OnCastTriggered);

	EnhancedInputComponent->BindAction(CastingInputAction, ETriggerEvent::Completed, this, &ThisClass::OnCastFinished);
}

void APlayerController_StairwayFishingGamePlayerController::OnCastStarted(const FInputActionInstance& InInputActionInstance)
{
	BroadcastCastDelegateAndValue(OnCastStartedDelegate, InInputActionInstance);
}

void APlayerController_StairwayFishingGamePlayerController::OnCastTriggered(const FInputActionInstance& InInputActionInstance)
{
	BroadcastCastDelegateAndValue(OnCastTriggeredDelegate, InInputActionInstance);
}

void APlayerController_StairwayFishingGamePlayerController::OnCastFinished(const FInputActionInstance& InInputActionInstance)
{
	BroadcastCastDelegateAndValue(OnCastCompletedDelegate, InInputActionInstance);
}

void APlayerController_StairwayFishingGamePlayerController::BroadcastCastDelegateAndValue(const FOnPlayerActionInput& InDelegate, const FInputActionInstance& InInputActionInstance) const
{
	if (!InDelegate.IsBound())
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Delegate is not bound, won't continue broadcasting message!"));
		return;
	}

	const float TriggeredTime = InInputActionInstance.GetElapsedTime();

	InDelegate.ExecuteIfBound(TriggeredTime);
}

bool APlayerController_StairwayFishingGamePlayerController::GetEnhancedInputLocalPlayerSubsystem(UEnhancedInputLocalPlayerSubsystem*& OutEnhancedInputLocalPlayerSubsystem) const
{
	bool bReturnValue = false;

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Local Player is not valid, this should not happen. Won't continue getting enhanced input local player subsystem..."));
		return bReturnValue;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!EnhancedInputLocalPlayerSubsystem)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Failed to cast Input Component to Enhanced Input Component, please make sure you have the Enhanced Input plugin enabled and that you set InputComponent field to EnhancedInputComponent in project settings!"));
		return bReturnValue;
	}

	OutEnhancedInputLocalPlayerSubsystem = EnhancedInputLocalPlayerSubsystem;
	bReturnValue = true;
	return bReturnValue;
}

bool APlayerController_StairwayFishingGamePlayerController::GetEnhancedInputComponent(UEnhancedInputComponent*& OutEnhancedInputComponent) const
{
	bool bReturnValue = false;

	if (!InputComponent)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Input Component is not valid, this should not happen. Won't continue getting enhanced input component..."));
		return bReturnValue;
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Failed to cast Input Component to Enhanced Input Component, please make sure you have the Enhanced Input plugin enabled and that you set InputComponent field to EnhancedInputComponent in project settings!"));
		return bReturnValue;
	}

	OutEnhancedInputComponent = EnhancedInputComponent;
	bReturnValue = true;
	return bReturnValue;
}