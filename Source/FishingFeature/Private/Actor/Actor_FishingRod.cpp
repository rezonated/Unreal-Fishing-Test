// Vanan Andreas - 2024


#include "Actor/Actor_FishingRod.h"

#include "DrawDebugHelpers.h"
#include "FishingFeature.h"
#include "Macros/TimelineMacro.h"


AActor_FishingRod::AActor_FishingRod()
{
	PrimaryActorTick.bCanEverTick = true;

	FishingRodMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FishingRodMeshComponent"));
	SetRootComponent(FishingRodMeshComponent);

	BobberMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BobberMeshComponent"));
	BobberMeshComponent->SetupAttachment(FishingRodMeshComponent);
}

void AActor_FishingRod::PrepareBobberTimeline()
{
	if (!BobberCurve)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Bobber Curve is not valid, have you set it up correctly in the component?"));
		return;
	}

	BIND_TIMELINE(ThrowFloatUpdate, &ThisClass::OnThrowUpdate, ThrowFinishedEvent, &ThisClass::OnThrowFinished)
	
	const float CurveLength = BobberCurve->FloatCurve.GetLastKey().Time;
	ThrowTimeline.SetTimelineLength(CurveLength);

	ThrowTimeline.AddInterpFloat(BobberCurve, ThrowFloatUpdate);
	ThrowTimeline.SetTimelineFinishedFunc(ThrowFinishedEvent);
}

void AActor_FishingRod::SetStartLocation()
{
	BobberStartLocation = BobberMeshComponent->GetComponentLocation();
}

void AActor_FishingRod::Throw(const FVector& InCastLocation)
{
	BobberTargetLocation = InCastLocation;
	
	ThrowTimeline.PlayFromStart();
}

void AActor_FishingRod::ReelBack()
{
	BobberTargetLocation = BobberStartLocation;
	
	ThrowTimeline.ReverseFromEnd();
}

void AActor_FishingRod::BeginPlay()
{
	Super::BeginPlay();

	PrepareBobberTimeline();
}

void AActor_FishingRod::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ThrowTimeline.IsPlaying())
	{
		ThrowTimeline.TickTimeline(DeltaSeconds);
	}
}

void AActor_FishingRod::OnThrowUpdate(float InAlpha)
{
	const float DeltaSeconds = GetWorld()->GetDeltaSeconds();

	const FVector InterpolatedLocationToReelIn = FMath::Lerp(BobberMeshComponent->GetComponentLocation(), BobberTargetLocation, InAlpha * DeltaSeconds);

	BobberMeshComponent->SetWorldLocationAndRotation(InterpolatedLocationToReelIn, FRotator::ZeroRotator);
}

void AActor_FishingRod::OnThrowFinished()
{
	ThrowFloatUpdate.Clear();
	ThrowFinishedEvent.Clear();

	bool bExecuteDelegate = CatchableLandsOnWaterDelegate.ExecuteIfBound();
}
