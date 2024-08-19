// Vanan Andreas - 2024


#include "ActorComponent/ActorComponent_FishingComponent.h"

#include "FishingFeature.h"
#include "FishingTags.h"
#include "DataAsset/DataAsset_FishingComponentConfig.h"
#include "Engine/AssetManager.h"
#include "GameInstanceSubsystem/VAGameplayMessagingSubsystem.h"
#include "Interface/CatchableInterface.h"
#include "Interface/CatcherInterface.h"
#include "Interface/PlayerActionInputInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Macros/TraceMacro.h"
#include "VACancellableAsyncAction/VAGameplayMessaging_ListenForGameplayMessages.h"


UActorComponent_FishingComponent::UActorComponent_FishingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentFishingState = FFishingTags::Get().FishingComponent_State_Idling;
}

void UActorComponent_FishingComponent::MockCast(const float& InElapsedTime)
{
	OnCastAction(InElapsedTime);
}

void UActorComponent_FishingComponent::MockCastEnd()
{
	OnCastActionEnded(0.f);
}

void UActorComponent_FishingComponent::RequestLoadFishingRodSoftClass()
{
	if (!FishingComponentConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Component Config is not valid, have you set it up correctly in the component?"));
		return;
	}

	const FFishingComponentConfig FishingComponentConfig = FishingComponentConfigData->GetFishingComponentConfig();

	const TSoftClassPtr<AActor> FishingRodActorClass = FishingComponentConfig.FishingRodActorClass;

	FishingRodAssetHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(FishingRodActorClass.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &ThisClass::OnFishingRodAssetLoaded));
}

void UActorComponent_FishingComponent::ListenForThrowNotify()
{
	NotifyMessageListenerAsync = UVAGameplayMessaging_ListenForGameplayMessages::ListenForGameplayMessagesViaChannel(this, FFishingTags::Get().Messaging_Fishing_Notify_Throw);

	NotifyMessageListenerAsync->OnGameplayMessageReceived.AddUniqueDynamic(this, &ThisClass::OnThrowNotifyMessageReceived);

	NotifyMessageListenerAsync->Activate();
}

void UActorComponent_FishingComponent::ListenForGameModeStateChangeFinish()
{
	GameModeStateChangeMessageListenerAsync = UVAGameplayMessaging_ListenForGameplayMessages::ListenForGameplayMessagesViaChannel(this, FFishingTags::Get().Messaging_GameMode_StateChangeFinish);

	GameModeStateChangeMessageListenerAsync->OnGameplayMessageReceived.AddUniqueDynamic(this, &ThisClass::OnGameModeStateChangeFinishMessageReceived);

	GameModeStateChangeMessageListenerAsync->Activate();
}

void UActorComponent_FishingComponent::BeginPlay()
{
	Super::BeginPlay();

	SetupInitialVectors();

	InitializeDecalActor();

	BindToPlayerActionInputDelegates();

	RequestLoadFishingRodSoftClass();

	ListenForThrowNotify();

	ListenForReelDoneNotify();

	ListenForGameModeStateChangeFinish();
}

void UActorComponent_FishingComponent::CleanupMessageListeners()
{
	if (IsValid(NotifyMessageListenerAsync))
	{
		NotifyMessageListenerAsync->Cancel();
		NotifyMessageListenerAsync = nullptr;
	}

	if (IsValid(GameModeStateChangeMessageListenerAsync))
	{
		GameModeStateChangeMessageListenerAsync->Cancel();
		GameModeStateChangeMessageListenerAsync = nullptr;
	}

	if (IsValid(ReelDoneDoneNotifyMessageListenerAsync))
	{
		ReelDoneDoneNotifyMessageListenerAsync->Cancel();
		ReelDoneDoneNotifyMessageListenerAsync = nullptr;
	}
}

void UActorComponent_FishingComponent::CleanupCatcherAndControllerDelegateBindings()
{
	if (CurrentCatcher)
	{
		CurrentCatcher->OnLandsOnWater().Unbind();

		CurrentCatcher = nullptr;
	}

	if (OwnerControllerAsPlayerActionInput)
	{
		OwnerControllerAsPlayerActionInput->OnCastActionStarted().Unbind();
		OwnerControllerAsPlayerActionInput->OnCastActionTriggered().Unbind();
		OwnerControllerAsPlayerActionInput->OnCastActionCompleted().Unbind();

		OwnerControllerAsPlayerActionInput = nullptr;
	}
}

void UActorComponent_FishingComponent::BeginDestroy()
{
	CleanupMessageListeners();

	CleanupCatcherAndControllerDelegateBindings();
	
	Super::BeginDestroy();
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

void UActorComponent_FishingComponent::OnFishingRodAssetLoaded()
{
	UObject* LoadedAsset = FishingRodAssetHandle.Get()->GetLoadedAsset();

	UClass* LoadedAssetAsClass = Cast<UClass>(LoadedAsset);
	if (!LoadedAssetAsClass)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Failed to cast loaded asset to UClass, this should not happen. Won't continue spawning fish..."));
		return;
	}

	if (!FishingComponentConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Component Config is not valid, have you set it up correctly in the component?"));
		return;
	}

	const FFishingComponentConfig FishingComponentConfig = FishingComponentConfigData->GetFishingComponentConfig();

	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Actor is not valid, won't continue initializing fishing rod..."));
		return;
	}

	USkeletalMeshComponent* ComponentAsSkeletalMeshComponent = nullptr;
	if (!GetOwnerSkeletalMeshComponent(ComponentAsSkeletalMeshComponent))
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Failed to get skeletal mesh component, won't continue initializing fishing rod..."));
		return;
	}

	const FName FishingPoleSocketName = FishingComponentConfig.FishingPoleSocketName;
	if (FishingPoleSocketName == NAME_None)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Pole Socket Name is not valid, have you set it up correctly in the data asset?"));
		return;
	}

	SpawnFishingRod(FishingPoleSocketName, ComponentAsSkeletalMeshComponent, LoadedAssetAsClass);
}

void UActorComponent_FishingComponent::SpawnFishingRod(const FName& InFishingPoleSocketName, USkeletalMeshComponent* InSkeletalMeshComponent, UClass* InFishingRodActorClass, ESpawnActorCollisionHandlingMethod InCollisionHandlingMethod)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("World is not valid, this should not happen. Won't continue spawning fish..."));
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = InCollisionHandlingMethod;

	AActor* FishingRodActor = World->SpawnActor<AActor>(InFishingRodActorClass, SpawnParameters);
	if (!FishingRodActor)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Failed to spawn fishing rod actor, won't continue spawning fish..."));
		return;
	}

	const bool bFishingRodActorImplementsCatcherInterface = FishingRodActor->Implements<UCatcherInterface>();
	if (!bFishingRodActorImplementsCatcherInterface)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Rod Actor does not implement ICatcherInterface, won't continue spawning fish..."));
		return;
	}

	CurrentCatcher = Cast<ICatcherInterface>(FishingRodActor);
	if (!CurrentCatcher)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Rod Actor does not implement ICatcherInterface, won't continue spawning fish..."));
		return;
	}

	FishingRodActor->AttachToComponent(InSkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, InFishingPoleSocketName);

	CurrentCatcher->OnLandsOnWater().BindUObject(this, &ThisClass::OnBobberLandsOnWater);
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

	OwnerControllerAsPlayerActionInput = Cast<IPlayerActionInputInterface>(OwnerController);
	if (!OwnerControllerAsPlayerActionInput)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Controller does not implement Player Action Input Interface, won't continue binding to player action input delegates..."));

		OwnerControllerAsPlayerActionInput = nullptr;
		return;
	}

	OwnerControllerAsPlayerActionInput->OnCastActionStarted().BindUObject(this, &ThisClass::OnCastAction);
	OwnerControllerAsPlayerActionInput->OnCastActionTriggered().BindUObject(this, &ThisClass::OnCastAction);
	OwnerControllerAsPlayerActionInput->OnCastActionCompleted().BindUObject(this, &ThisClass::OnCastActionEnded);
}

void UActorComponent_FishingComponent::OnCastAction(const float& InElapsedTime)
{
	if (CurrentFishingState == FFishingTags::Get().FishingComponent_State_AbleToReel)
	{
		if (CurrentCatchable && CurrentCatcher)
		{
			USceneComponent* AttachPoint = CurrentCatcher->GetCatchableAttachPoint();
			if (!AttachPoint)
			{
				UE_LOG(LogFishingFeature, Error, TEXT("Catching Rod is not valid, won't continue catching..."));
				return;
			}

			CurrentCatchable->Catch(AttachPoint);

			CurrentCatcher->ToggleBobberVisibility(false);

			ReelBack();

			MockReelInDoneDelegate.ExecuteIfBound(true);
		}
	}

	if (CurrentFishingState == FFishingTags::Get().FishingComponent_State_Idling)
	{
		const float MappedElapsedTime = GetMappedElapsedTimeToMaximumCastTime(InElapsedTime);

		BroadcastUIMessage(MappedElapsedTime);

		ToggleDecalVisibility(true);

		DetermineCastLocation(InElapsedTime);
	}
}

void UActorComponent_FishingComponent::ResetStateAndTimer()
{
	CurrentFishingState = FFishingTags::Get().FishingComponent_State_AbleToReel;

	GetWorld()->GetTimerManager().ClearTimer(CastTimerHandle);
}

void UActorComponent_FishingComponent::AttemptGetNearestCatchable()
{
	if (!FishingComponentConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Component Config is not valid, have you set it up correctly in the component?"));
		return;
	}

	const FFishingComponentConfig FishingComponentConfig = FishingComponentConfigData->GetFishingComponentConfig();

	const float CastRadius = FishingComponentConfig.CastRadius;

	TArray<FHitResult> HitResult;

	const bool bSphereTraceForCatchables = UKismetSystemLibrary::SphereTraceMulti(this, CastLocation, CastLocation, CastRadius, UEngineTypes::ConvertToTraceType(ECC_Visibility), true, TArray<AActor*>{}, EDrawDebugTrace::Type::None, HitResult, true, FLinearColor::Yellow, FLinearColor::Red, 0.f);

	if (!bSphereTraceForCatchables)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Failed to trace for catchables, won't continue..."));
		return;
	}

	TArray<AActor*> CatchableActors;

	for (const FHitResult& HitResultItem : HitResult)
	{
		AActor* HitActor = HitResultItem.Actor.Get();
		if (!HitActor)
		{
			continue;
		}

		const bool bHitActorImplementsCatchable = HitActor->Implements<UCatchableInterface>();
		if (!bHitActorImplementsCatchable)
		{
			continue;
		}

		CatchableActors.AddUnique(HitActor);
	}

	const bool bCatchableActorsAreValid = CatchableActors.Num() > 0;
	if (!bCatchableActorsAreValid)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("No valid catchable actors found, won't continue..."));
		return;
	}

	FVector LocationReference = CastLocation;
	CatchableActors.Sort([LocationReference](const AActor& A, const AActor& B) {
		// Calculate the squared distance to avoid the cost of square root calculations
		const float DistanceA = FVector::DistSquared(A.GetActorLocation(), LocationReference);
		const float DistanceB = FVector::DistSquared(B.GetActorLocation(), LocationReference);

		// Sort in ascending order (nearest first)
		return DistanceA < DistanceB;
	});

	CurrentCatchable = Cast<ICatchableInterface>(CatchableActors[0]);
	if (!CurrentCatchable)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Random Catchable is not valid, won't continue..."));

		CurrentCatchable = nullptr;

		MockAbleToCatchFishDoneDelegate.ExecuteIfBound(false);
	}

	MockAbleToCatchFishDoneDelegate.ExecuteIfBound(true);
}

void UActorComponent_FishingComponent::ReelInCurrentCatchable()
{
	if (!CurrentCatchable)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Current Catchable is not valid, won't continue..."));
		return;
	}

	CurrentCatchable->ReeledIn(CastLocation);
}

void UActorComponent_FishingComponent::StartWaitingForFishTimer()
{
	if (!FishingComponentConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Component Config is not valid, have you set it up correctly in the component?"));
		return;
	}

	const FFishingComponentConfig FishingComponentConfig = FishingComponentConfigData->GetFishingComponentConfig();

	CurrentFishingState = FFishingTags::Get().FishingComponent_State_WaitingForFish;

	const float TimeToFish = FishingComponentConfig.TimeToFish;

	GetWorld()->GetTimerManager().SetTimer(CastTimerHandle, this, &ThisClass::ResetStateAndTimer, TimeToFish, false);
}

void UActorComponent_FishingComponent::LetCatchableEscape()
{
	if (CurrentCatchable)
	{
		CurrentCatchable->Escape();
		CurrentCatchable = nullptr;
	}
}

void UActorComponent_FishingComponent::ReelBack()
{
	UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_Fishing_AnimInstance_StateChange, FFishingTags::Get().AnimInstance_Fishing_State_Reeling_In);

	CurrentFishingState = FFishingTags::Get().FishingComponent_State_Reeling_Out;

	CurrentCatcher->ReelBack();
}

void UActorComponent_FishingComponent::ListenForReelDoneNotify()
{
	ReelDoneDoneNotifyMessageListenerAsync = UVAGameplayMessaging_ListenForGameplayMessages::ListenForGameplayMessagesViaChannel(this, FFishingTags::Get().Messaging_Fishing_Notify_ReelDone);

	ReelDoneDoneNotifyMessageListenerAsync->OnGameplayMessageReceived.AddUniqueDynamic(this, &ThisClass::OnReelDoneNotifyMessageReceived);

	ReelDoneDoneNotifyMessageListenerAsync->Activate();
}

void UActorComponent_FishingComponent::OnCastActionEnded(const float&)
{
	if (CurrentFishingState == FFishingTags::Get().FishingComponent_State_WaitingForFish)
	{
		LetCatchableEscape();

		ResetStateAndTimer();

		ReelBack();

		MockReelInDoneDelegate.ExecuteIfBound(false);

		return;
	}

	if (CurrentFishingState == FFishingTags::Get().FishingComponent_State_Throwing || CurrentFishingState == FFishingTags::Get().FishingComponent_State_Reeling_In || CurrentFishingState == FFishingTags::Get().FishingComponent_State_Reeling_Out)
	{
		return;
	}

	BroadcastUIMessage(0.f);

	ToggleDecalVisibility(false);

	const bool bIsCastTimerActive = GetWorld()->GetTimerManager().IsTimerActive(CastTimerHandle);
	if (bIsCastTimerActive) // Exit early if cast timer is still active, means we're still casting. Fail it, reset cast flag and timer then return.
	{
		ResetStateAndTimer();
		return;
	}

	if (CurrentCatchable)
	{
		return;
	}

	UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_Fishing_AnimInstance_StateChange, FFishingTags::Get().AnimInstance_Fishing_State_Throwing);

	CurrentFishingState = FFishingTags::Get().FishingComponent_State_Throwing;
}

void UActorComponent_FishingComponent::OnBobberLandsOnWater()
{
	AttemptGetNearestCatchable();

	StartWaitingForFishTimer();

	ReelInCurrentCatchable();

	MockBobberLandsOnWaterDelegate.ExecuteIfBound(true);
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

	SetDecalActorLocation(InCastStartPosition);
}

void UActorComponent_FishingComponent::BroadcastUIMessage(const float& InProgress) const
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

bool UActorComponent_FishingComponent::GetOwnerSkeletalMeshComponent(
	USkeletalMeshComponent*& OutSkeletalMeshComponent) const
{
	bool bReturnValue = false;

	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Actor is not valid, won't continue getting skeletal mesh component..."));
		return bReturnValue;
	}

	UActorComponent* ActorComponent = OwnerActor->GetComponentByClass(USkeletalMeshComponent::StaticClass());
	if (!ActorComponent)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Actor does not have a SkeletalMeshComponent, won't continue getting skeletal mesh component..."));
		return bReturnValue;
	}

	OutSkeletalMeshComponent = Cast<USkeletalMeshComponent>(ActorComponent);
	if (!OutSkeletalMeshComponent)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Actor does not have a SkeletalMeshComponent, won't continue getting skeletal mesh component..."));
		return bReturnValue;
	}

	bReturnValue = true;
	return bReturnValue;
}

void UActorComponent_FishingComponent::OnThrowNotifyMessageReceived(const FGameplayTag& Channel, const FVAAnyUnreal& MessagePayload)
{
	if (!CurrentCatcher)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Current Catcher is not valid, won't continue..."));
		return;
	}

	CurrentCatcher->Throw(CastLocation);
}

void UActorComponent_FishingComponent::OnReelDoneNotifyMessageReceived(const FGameplayTag& Channel,
	const FVAAnyUnreal&                                                                    MessagePayload)
{
	UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_Fishing_AnimInstance_StateChange, FFishingTags::Get().AnimInstance_Fishing_State_Idling);

	CurrentFishingState = FFishingTags::Get().FishingComponent_State_Idling;

	if (!CurrentCatchable)
	{
		// Fail to catch any fish, don't transition to show fish state
		return;
	}

	const FVAAnyUnreal Payload = FFishingTags::Get().FishingGameLoopState_ShowFish;

	UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_GameState_StateChange, Payload);
}

void UActorComponent_FishingComponent::OnGameModeStateChangeFinishMessageReceived(const FGameplayTag& Channel,
	const FVAAnyUnreal&                                                                               MessagePayload)
{
	if (!MessagePayload.Is<FGameplayTag>())
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Message payload is not a gameplay tag, have you correctly send the tag value? Won't continue..."));
		return;
	}

	const FGameplayTag Payload = MessagePayload.Get<FGameplayTag>();

	if (!Payload.IsValid())
	{
		 UE_LOG(LogFishingFeature, Error, TEXT("Payload tag is not valid, have you correctly send the tag value? Won't continue..."));
		 return;
	}

	if (!CurrentCatchable)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Current Catchable is not valid, won't continue..."));
		return;
	}

	UObject* CatchableObject = CurrentCatchable->_getUObject();
	if (!CatchableObject)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Catchable Object is not valid, won't continue..."));
		return;
	}

	if (!CurrentCatcher)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Current Catcher is not valid, won't continue..."));
		return;
	}

	const bool bIsFishingGameLoopState = Payload.MatchesTag(FFishingTags::Get().FishingGameLoopState_Fishing);

	CurrentCatcher->ToggleCatcherVisibility(bIsFishingGameLoopState);
	CurrentCatcher->ToggleBobberVisibility(true);

	if (bIsFishingGameLoopState)
	{
		CurrentCatcher->ToggleCatcherVisibility(true);

		CatchableObject->ConditionalBeginDestroy();
		CurrentCatchable = nullptr;

		UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_Fishing_AnimInstance_StateChange, FFishingTags::Get().AnimInstance_Fishing_State_Idling);
		return;
	}

	CurrentCatcher->ToggleCatcherVisibility(false);

	AActor* CatchableActor = Cast<AActor>(CatchableObject);
	if (!CatchableActor)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Catchable Actor is not valid, won't continue..."));
		return;
	}

	if (!FishingComponentConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Fishing Component Config is not valid, have you set it up correctly in the component?"));
		return;
	}

	const FFishingComponentConfig FishingComponentConfig = FishingComponentConfigData->GetFishingComponentConfig();
	const FName CarryFishSocketName = FishingComponentConfig.CarryFishSocketName;

	if (CarryFishSocketName == NAME_None)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Carry Fish Socket Name is not valid, have you set it up correctly in the data asset?"));
		return;
	}

	UVAGameplayMessagingSubsystem::Get(this).BroadcastMessage(this, FFishingTags::Get().Messaging_Fishing_AnimInstance_StateChange, FFishingTags::Get().AnimInstance_Fishing_State_ShowFish);

	USkeletalMeshComponent* OwnerSkeletalMeshComponent = nullptr;
	if (!GetOwnerSkeletalMeshComponent(OwnerSkeletalMeshComponent))
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Owner Skeletal Mesh Component is not valid, won't continue..."));
		return;
	}

	CatchableActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	CatchableActor->SetActorTransform(FTransform::Identity);

	CatchableActor->AttachToComponent(OwnerSkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, CarryFishSocketName);
}