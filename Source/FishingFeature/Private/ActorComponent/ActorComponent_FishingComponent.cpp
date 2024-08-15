// Vanan Andreas - 2024


#include "ActorComponent/ActorComponent_FishingComponent.h"

#include "FishingFeature.h"
#include "FishingTags.h"
#include "DataAsset/DataAsset_FishingComponentConfig.h"
#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"
#include "Interface/PlayerActionInputInterface.h"
#include "Kismet/KismetSystemLibrary.h"


UActorComponent_FishingComponent::UActorComponent_FishingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UActorComponent_FishingComponent::BeginPlay()
{
	Super::BeginPlay();

	BindToPlayerActionInputDelegates();
}

void UActorComponent_FishingComponent::BindToPlayerActionInputDelegates()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Actor is not valid, won't continue binding to player action input delegates..."));
		return;
	}

	const APawn* OwnerAsPawn = Cast<APawn>(OwnerActor);
	if (!OwnerAsPawn)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Actor is not a Pawn, won't continue binding to player action input delegates..."));
		return;
	}

	AController* OwnerController = OwnerAsPawn->Controller;
	if (!OwnerController)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Controller is not valid, won't continue binding to player action input delegates..."));
		return;
	}

	const bool bOwnerControllerImplementsPlayerActionInput = OwnerController->Implements<UPlayerActionInputInterface>();
	if (!bOwnerControllerImplementsPlayerActionInput)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Controller does not implement Player Action Input Interface, won't continue binding to player action input delegates..."));
		return;
	}

	IPlayerActionInputInterface* OwnerControllerAsPlayerActionInput = Cast<IPlayerActionInputInterface>(OwnerController);
	if (!OwnerControllerAsPlayerActionInput)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Controller does not implement Player Action Input Interface, won't continue binding to player action input delegates..."));
		return;
	}

	OwnerControllerAsPlayerActionInput->OnCastActionStarted().AddUObject(this, &ThisClass::OnCastAction);
	OwnerControllerAsPlayerActionInput->OnCastActionTriggered().AddUObject(this, &ThisClass::OnCastAction);
	OwnerControllerAsPlayerActionInput->OnCastActionCompleted().AddUObject(this, &ThisClass::OnCastActionEnded);
}

void UActorComponent_FishingComponent::OnCastAction(const float& InElapsedTime)
{
	if (!FishingComponentConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Component Config is not valid, have you set it up correctly in the component?"));
		return;
	}
	
	const float MappedProgress = GetMappedProgress(InElapsedTime);

	UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_Fishing_UI_Cast_Update, MappedProgress);

	const FFishingComponentConfig FishingComponentConfig = FishingComponentConfigData->GetFishingComponentConfig();
	
	const float CastDistance = FishingComponentConfig.MaximumCastDistance;
	
	// TODO: Cast fishing line
}

void UActorComponent_FishingComponent::OnCastActionEnded(const float&)
{
	UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_Fishing_UI_Cast_Update, 0.f);
}

float UActorComponent_FishingComponent::GetMappedProgress(const float& InValue, const float DefaultValue) const
{
	float ReturnValue = DefaultValue;
	if (!FishingComponentConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Component Config is not valid, have you set it up correctly in the component?"));
		return ReturnValue;
	}

	const FFishingComponentConfig FishingComponentConfig = FishingComponentConfigData->GetFishingComponentConfig();

	const float MaximumTimeToCast = FishingComponentConfig.MaximumTimeToCast;
	
	ReturnValue = FMath::GetMappedRangeValueClamped(FVector2D(0.f, MaximumTimeToCast), FVector2D(0.f, 1.f), InValue);

	return ReturnValue;
}
