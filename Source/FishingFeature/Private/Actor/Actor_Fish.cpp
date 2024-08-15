// Vanan Andreas - 2024


#include "Actor/Actor_Fish.h"

#include "FishingFeature.h"
#include "Components/SphereComponent.h"
#include "DataAsset/DataAsset_ActorFishConfig.h"
#include "Kismet/KismetMathLibrary.h"
#include "Macros/TimelineMacro.h"
#include "Struct/ActorFishConfig.h"

AActor_Fish::AActor_Fish()
{
	PrimaryActorTick.bCanEverTick = true;

	FishSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Fish Sphere Collision"));
	SetRootComponent(FishSphereCollision);

	FishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fish Mesh"));
	FishMesh->SetupAttachment(FishSphereCollision);
	FishMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AActor_Fish::ReeledIn(const FVector& RodLocation)
{
	ReelInLocation = RodLocation;

	LookAtReelInRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ReelInLocation);

	ReelInTimeline.PlayFromStart();
}

void AActor_Fish::Escape()
{
	ReelInTimeline.Stop();
		
	EscapeRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), InitialActorLocation);
		
	EscapeTimeline.Play();
}

void AActor_Fish::BeginPlay()
{
	Super::BeginPlay();

	InitialActorLocation = GetActorLocation();
	
	SetupTimelines();
}

void AActor_Fish::SetupTimelines()
{
	if (!ActorFishConfigData)
	{
		UE_LOG(LogFishingFeature, Error, TEXT("Actor Fish Config is not valid, have you set it up correctly in the component?"));
		return;
	}

	const FActorFishConfig FishConfig = ActorFishConfigData->GetActorFishConfig();

	UCurveFloat* FishReelingInCurve = FishConfig.FishReelingInCurve;
	if (FishReelingInCurve)
	{
		BIND_TIMELINE(ReelInFloatUpdate, &ThisClass::OnReelInUpdate, ReelInFinishedEvent, &ThisClass::OnReelInFinished)
		
		SetupTimelineDataAndCallbacks(&ReelInTimeline, ReelInFloatUpdate, ReelInFinishedEvent, FishReelingInCurve);
	}

	UCurveFloat* FishEscapeCurve = FishConfig.FishEscapedCurve;
	if (FishEscapeCurve)
	{
		BIND_TIMELINE(EscapeFloatUpdate, &ThisClass::OnEscapeUpdate, EscapeFinishedEvent, &ThisClass::OnEscapeFinished)
		
		SetupTimelineDataAndCallbacks(&EscapeTimeline, EscapeFloatUpdate, EscapeFinishedEvent, FishEscapeCurve);
	}
}

void AActor_Fish::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ReelInTimeline.IsPlaying())
	{
		ReelInTimeline.TickTimeline(DeltaSeconds);
	}

	if (EscapeTimeline.IsPlaying())
	{
		EscapeTimeline.TickTimeline(DeltaSeconds);
	}
}

void AActor_Fish::SetupTimelineDataAndCallbacks(FTimeline* InTimeline, const FOnTimelineFloat& InOnTimelineFloat, const FOnTimelineEvent& InOnTimelineEvent, UCurveFloat* InCurveFloat) const
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

void AActor_Fish::ClearTimeline(FOnTimelineFloat* InTimelineFloat, FOnTimelineEvent* InTimelineEvent)
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

void AActor_Fish::OnReelInUpdate(float InAlpha)
{
	InterpolateLocationAndRotation(ReelInLocation, LookAtReelInRotation, InAlpha);
}

void AActor_Fish::InterpolateLocationAndRotation(const FVector& InTargetLocation, const FRotator& InTargetRotation, const float& InAlpha)
{
	const float DeltaSeconds = GetWorld()->GetDeltaSeconds();

	const FVector InterpolatedLocationToReelIn = FMath::Lerp(GetActorLocation(), InTargetLocation, InAlpha * DeltaSeconds);
	const FRotator InterpolatedRotationToReelIn = FMath::Lerp(GetActorRotation(), InTargetRotation, InAlpha * DeltaSeconds);

	SetActorLocationAndRotation(InterpolatedLocationToReelIn, InterpolatedRotationToReelIn);
}

void AActor_Fish::OnReelInFinished()
{
	ClearTimeline(&ReelInFloatUpdate, &ReelInFinishedEvent);
	
	// TODO: Send event, somehow!
}

void AActor_Fish::OnEscapeUpdate(float InAlpha)
{
	InterpolateLocationAndRotation(InitialActorLocation, EscapeRotation, InAlpha);
}

void AActor_Fish::OnEscapeFinished()
{
	ClearTimeline(&EscapeFloatUpdate, &EscapeFinishedEvent);
}
