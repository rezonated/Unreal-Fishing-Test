// Vanan Andreas - 2024


#include "Actor/Actor_FishingRod.h"

#include "FishingFeature.h"
#include "DataAsset/DataAsset_FishingRodConfig.h"
#include "Macros/TimelineMacro.h"
#include "Struct/FishingRodConfig.h"


AActor_FishingRod::AActor_FishingRod()
{
	PrimaryActorTick.bCanEverTick = true;

	FishingRodMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FishingRodMeshComponent"));
	SetRootComponent(FishingRodMeshComponent);

	BobberMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BobberMeshComponent"));
	BobberMeshComponent->SetupAttachment(FishingRodMeshComponent);

	CatchableAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("CatchableAttachPoint"));
	CatchableAttachPoint->SetupAttachment(BobberMeshComponent);
}

void AActor_FishingRod::Throw(const FVector& InCastLocation)
{
	BobberTargetLocation = InCastLocation;

	ThrowReelInTimeline.PlayFromStart();
}

void AActor_FishingRod::ReelBack()
{
	BobberTargetLocation = BobberStartLocation;

	PullReelOutTimeline.PlayFromStart();
}

void AActor_FishingRod::ToggleBobberVisibility(const bool& bInShouldBeVisible)
{
	if (!BobberMeshComponent)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Bobber Mesh Component is not valid, won't continue toggling visibility..."));
		return;
	}

	BobberMeshComponent->SetVisibility(bInShouldBeVisible);
}

void AActor_FishingRod::ToggleCatcherVisibility(const bool& bInShouldBeVisible)
{
	SetActorHiddenInGame(!bInShouldBeVisible);
}

void AActor_FishingRod::BeginPlay()
{
	Super::BeginPlay();

	SetupTimelines();

	GetWorld()->GetTimerManager().SetTimerForNextTick([&]() {
		BobberStartLocation = BobberMeshComponent->GetComponentLocation();
	});
}


void AActor_FishingRod::TickTimelines(float DeltaSeconds)
{
	if (ThrowReelInTimeline.IsPlaying())
	{
		ThrowReelInTimeline.TickTimeline(DeltaSeconds);
	}

	if (PullReelOutTimeline.IsPlaying())
	{
		PullReelOutTimeline.TickTimeline(DeltaSeconds);
	}
}

void AActor_FishingRod::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TickTimelines(DeltaSeconds);
}

void AActor_FishingRod::SetupTimelines()
{
	if (!FishingRodConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Actor Fish Config is not valid, have you set it up correctly in the component?"));
		return;
	}

	const FFishingRodConfig FishingRodConfig = FishingRodConfigData->GetFishingRodConfig();

	UCurveFloat* BobberReelInCurve = FishingRodConfig.BobberReelInCurve;
	if (BobberReelInCurve)
	{
		BIND_TIMELINE(ThrowReelInFloatUpdate, &ThisClass::OnThrowReelInUpdate, ThrowReelInFinishedEvent, &ThisClass::OnThrowReelInFinished)

		SetupTimelineDataAndCallbacks(&ThrowReelInTimeline, ThrowReelInFloatUpdate, ThrowReelInFinishedEvent, BobberReelInCurve);
	}

	UCurveFloat* BobberReelOutCurve = FishingRodConfig.BobberReelOutCurve;
	if (BobberReelOutCurve)
	{
		BIND_TIMELINE(PullReelOutFloatUpdate, &ThisClass::OnPullReelOutUpdate, PullReelOutFinishedEvent, &ThisClass::OnPullReelOutFinished)

		SetupTimelineDataAndCallbacks(&PullReelOutTimeline, PullReelOutFloatUpdate, PullReelOutFinishedEvent, BobberReelOutCurve);
	}
}

void AActor_FishingRod::SetupTimelineDataAndCallbacks(FTimeline* InTimeline, const FOnTimelineFloat& InOnTimelineFloat, const FOnTimelineEvent& InOnTimelineEvent, UCurveFloat* InCurveFloat) const
{
	if (!InTimeline)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Timeline is not valid, did you pass the correct pointer?"));
		return;
	}

	const float CurveLength = InCurveFloat->FloatCurve.GetLastKey().Time;
	InTimeline->SetTimelineLength(CurveLength);

	InTimeline->AddInterpFloat(InCurveFloat, InOnTimelineFloat);
	InTimeline->SetTimelineFinishedFunc(InOnTimelineEvent);
}

void AActor_FishingRod::ClearTimeline(FOnTimelineFloat* InTimelineFloat, FOnTimelineEvent* InTimelineEvent)
{
	if (InTimelineFloat)
	{
		InTimelineFloat->Clear();
	}

	if (InTimelineEvent)
	{
		InTimelineEvent->Clear();
	}
}

void AActor_FishingRod::OnThrowReelInUpdate(float InAlpha)
{
	InterpolateBobberLocation(InAlpha);
}

void AActor_FishingRod::OnThrowReelInFinished()
{
	ClearTimeline(&ThrowReelInFloatUpdate, &ThrowReelInFinishedEvent);

	CatchableLandsOnWaterDelegate.ExecuteIfBound();
}

void AActor_FishingRod::OnPullReelOutUpdate(float InAlpha)
{
	InterpolateBobberLocation(InAlpha);
}

void AActor_FishingRod::OnPullReelOutFinished()
{
	ClearTimeline(&PullReelOutFloatUpdate, &PullReelOutFinishedEvent);
}

void AActor_FishingRod::InterpolateBobberLocation(const float& InAlpha) const
{
	const float   DeltaSeconds = GetWorld()->GetDeltaSeconds();
	const FVector InterpolatedLocationToReelIn = FMath::Lerp(BobberMeshComponent->GetComponentLocation(), BobberTargetLocation, InAlpha * DeltaSeconds);

	BobberMeshComponent->SetWorldLocationAndRotation(InterpolatedLocationToReelIn, FRotator::ZeroRotator);
}