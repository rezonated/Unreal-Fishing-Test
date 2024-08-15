// Vanan Andreas - 2024


#include "PlayerController/StairwayFishingGamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "StairwayFishingGameCore.h"

void AStairwayFishingGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	MapInputContext(DefaultInputMappingContext);

	MapInputActions();
}

void AStairwayFishingGamePlayerController::MapInputContext(const UInputMappingContext* InMappingContext, const int32& InPriority, const bool& bInClearExistingMappings) const
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

void AStairwayFishingGamePlayerController::MapInputActions()
{
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	if(!GetEnhancedInputComponent(EnhancedInputComponent))
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

void AStairwayFishingGamePlayerController::OnCastStarted(const FInputActionInstance& InInputActionInstance)
{
	BroadcastCastEventsAndValues(OnCastStartedDelegate, InInputActionInstance);
}

void AStairwayFishingGamePlayerController::OnCastTriggered(const FInputActionInstance& InInputActionInstance)
{
	 BroadcastCastEventsAndValues(OnTriggeredDelegate, InInputActionInstance);
}

void AStairwayFishingGamePlayerController::OnCastFinished(const FInputActionInstance& InInputActionInstance)
{
	 BroadcastCastEventsAndValues(OnCastFinishedDelegate, InInputActionInstance);
}

void AStairwayFishingGamePlayerController::BroadcastCastEventsAndValues(const FPlayerActionDelegate& InDelegate, const FInputActionInstance& InInputActionInstance)
{
	const float TriggeredTime = InInputActionInstance.GetTriggeredTime();

	GEngine->AddOnScreenDebugMessage(-1, TriggeredTime, FColor::Red, FString::Printf(TEXT("Triggered Time: %f"), TriggeredTime));

	if (!InDelegate.IsBound())
	{
		return;
	}
	
	InDelegate.Execute(TriggeredTime);
}

bool AStairwayFishingGamePlayerController::GetEnhancedInputLocalPlayerSubsystem(UEnhancedInputLocalPlayerSubsystem*& OutEnhancedInputLocalPlayerSubsystem) const
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

bool AStairwayFishingGamePlayerController::GetEnhancedInputComponent(UEnhancedInputComponent*& OutEnhancedInputComponent) const
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
