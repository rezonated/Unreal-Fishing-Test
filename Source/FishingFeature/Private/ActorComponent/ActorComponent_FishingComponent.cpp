// Vanan Andreas - 2024


#include "ActorComponent/ActorComponent_FishingComponent.h"

#include "FishingFeature.h"
#include "FishingTags.h"
#include "DataAsset/DataAsset_FishingComponentConfig.h"
#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"
#include "Interface/PlayerActionInputInterface.h"
#include "Macros/TraceMacros.h"


UActorComponent_FishingComponent::UActorComponent_FishingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UActorComponent_FishingComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupInitialVectors();

	InitializeDecalActor();

	BindToPlayerActionInputDelegates();
}

void UActorComponent_FishingComponent::SetupInitialVectors()
{
	const AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return;
	}
	
	InitialActorLocation = OwnerActor->GetActorLocation();
	InitialActorForwardVector = OwnerActor->GetActorForwardVector();
}

void UActorComponent_FishingComponent::InitializeDecalActor()
{
	if (!FishingComponentConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Component Config is not valid, have you set it up correctly in the component?"));
		return;
	}

	const FFishingComponentConfig FishingComponentConfig = FishingComponentConfigData->GetFishingComponentConfig();

	if (!FishingComponentConfig.TargetActorDecalClass)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Target Actor Decal Class is not valid, have you set it up correctly in the data asset?"));
		return;
	}

	const AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Actor is not valid, won't continue initializing decal actor..."));
		return;
	}

	TargetActorDecalInstance = GetWorld()->SpawnActor<AActor>(FishingComponentConfig.TargetActorDecalClass);
	if (!TargetActorDecalInstance)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Failed to spawn decal actor, won't continue initializing decal actor..."));
		return;
	}

	ToggleDecalVisibility(false);
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
	
	const float MappedElapsedTime = GetMappedElapsedTimeToMaximumCastTime(InElapsedTime);

	BroadcastUIMessage(MappedElapsedTime);

	ToggleDecalVisibility(true);

	DetermineCastLocation(InElapsedTime);
}

void UActorComponent_FishingComponent::OnCastActionEnded(const float&)
{
	BroadcastUIMessage(0.f);

	ToggleDecalVisibility(false);
}

void UActorComponent_FishingComponent::DetermineCastLocation(const float& InElapsedTime)
{
	if (!FishingComponentConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Component Config is not valid, have you set it up correctly in the component?"));
		return;
	}

	const FFishingComponentConfig FishingComponentConfig = FishingComponentConfigData->GetFishingComponentConfig();

	const float MaximumTimeToCast = FishingComponentConfig.MaximumTimeToCast;

	const float MinimumCastDistance = FishingComponentConfig.MinimumCastDistance;

	const float MaximumCastDistance = FishingComponentConfig.MaximumCastDistance;

	const float MappedForwardDistance = FMath::GetMappedRangeValueClamped(FVector2D(0.f, MaximumTimeToCast), FVector2D(MinimumCastDistance, MaximumCastDistance), InElapsedTime);

	const FVector ForwardDirection = InitialActorForwardVector * MappedForwardDistance;
	
	const FVector CastStartPosition = InitialActorLocation + ForwardDirection;

	AttemptToCast(CastStartPosition);
}

void UActorComponent_FishingComponent::AttemptToCast(const FVector& InCastStartPosition)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("World is not valid, this should never happen... won't continue casting..."));
		return;
	}

	const FVector TraceEnd = InCastStartPosition + FVector::DownVector * 1000.f;
	
	FHitResult HitResult;
	
	ECollisionChannel TraceWaterBodyChannel = UEngineTypes::ConvertToCollisionChannel(TRACE_WATER_BODY);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	
	const bool bTraceToWater = World->LineTraceSingleByObjectType(HitResult, InCastStartPosition, TraceEnd, FCollisionObjectQueryParams(TraceWaterBodyChannel), QueryParams);

	if (!bTraceToWater)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Failed to trace to water, won't continue..."));
		return;
	}

	if (!HitResult.bBlockingHit)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Trace did not hit a blocking hit, won't continue..."));
		return;
	}

	AActor* HitActor = HitResult.GetActor();
	if (!HitActor)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Hit Actor is not valid, won't continue..."));
		return;
	}

	CastLocation = HitResult.Location;

	SetDecalActorLocation(CastLocation);
}

void UActorComponent_FishingComponent::BroadcastUIMessage(const float& InProgress)
{
	 UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_Fishing_UI_Cast_Update, InProgress);
}

float UActorComponent_FishingComponent::GetMappedElapsedTimeToMaximumCastTime(const float& InValue, const float DefaultValue) const
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

void UActorComponent_FishingComponent::ToggleDecalVisibility(const bool& bInShouldBeVisible) const
{
	if (!TargetActorDecalInstance)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Target Actor Decal Instance is not valid, perhaps it has not been initialized. Won't continue toggling decal visibility..."));
		return;
	}

	if (!bInShouldBeVisible == TargetActorDecalInstance->IsHidden())
	{
		return;
	}

	TargetActorDecalInstance->SetActorHiddenInGame(!bInShouldBeVisible);
}

void UActorComponent_FishingComponent::SetDecalActorLocation(const FVector& InLocation) const
{
	if (!TargetActorDecalInstance)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Target Actor Decal Instance is not valid, perhaps it has not been initialized. Won't continue setting decal location..."));
		return;
	}

	TargetActorDecalInstance->SetActorLocation(InLocation);
}
