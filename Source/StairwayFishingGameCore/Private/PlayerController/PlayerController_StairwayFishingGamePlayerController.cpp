// Vanan Andreas - 2024


#include "PlayerController/PlayerController_StairwayFishingGamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FishingTags.h"
#include "StairwayFishingGameCore.h"
#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"
#include "Runtime/VAAnyUnreal.h"

void APlayerController_StairwayFishingGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeGameOnly());

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

void APlayerController_StairwayFishingGamePlayerController::OnCastStarted(const FInputActionInstance& InInputActionInstance)
{
	BroadcastCastMessage(FFishingTags::Get().Messaging_Fishing_Cast_Started, InInputActionInstance);
}

void APlayerController_StairwayFishingGamePlayerController::OnCastTriggered(const FInputActionInstance& InInputActionInstance)
{
	BroadcastCastMessage(FFishingTags::Get().Messaging_Fishing_Cast_Held, InInputActionInstance);
}

void APlayerController_StairwayFishingGamePlayerController::OnCastFinished(const FInputActionInstance& InInputActionInstance)
{
	 BroadcastCastMessage(FFishingTags::Get().Messaging_Fishing_Cast_Finished, InInputActionInstance);
}

void APlayerController_StairwayFishingGamePlayerController::BroadcastCastMessage(const FGameplayTag& InChannelTag, const FInputActionInstance& InInputActionInstance) const
{
	if (!InChannelTag.IsValid())
	{
		UE_LOG(LogStairwayFishingGameCore, Error, TEXT("Channel Tag is not valid, won't continue broadcasting message!"));
		return;
	}

	const FString ChannelTagString = InChannelTag.ToString();
	GEngine->AddOnScreenDebugMessage(1, .1f, FColor::Cyan, FString::Printf(TEXT("Broadcasting Message: %s"), *ChannelTagString));

	UVAGameplayMessagingSubsystem& GameplayMessagingSubsystem = UVAGameplayMessagingSubsystem::Get(this);

	const float TriggeredTime = InInputActionInstance.GetTriggeredTime();

	GameplayMessagingSubsystem.BroadcastMessage(this, InChannelTag, TriggeredTime);
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
