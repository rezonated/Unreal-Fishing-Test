// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/CatchableInterface.h"
#include "Actor_Fish.generated.h"

class UDataAsset_ActorFishConfig;
class USphereComponent;

/*
 * Fish actor class, handles fish movement and able to be caught by a fishing rod - thus implementing the ICatchableInterface interface.
 * 
 * The fish is able to swim around a certain area inside a extent by getting random locations inside the extent and lerps
 * current position, rotation to the randomized target location and rotation to simulate a fish swimming around.
 * 
 * When the fish is caught, it will attach to the scene component provided by ICatcherInterface.
 * 
 * Parameters for this fish actor are set in the DA_ActorFishConfig data asset, can be tuned and tweaked to your liking.
 * 
 * The fish can also escape when the player is too early reeling out the fishing rod, it just simply lerps back to the original location and rotation.
 * 
 * The fish that is closest to the bobber location of the fishing rod will be caught and when the fish escapes,
 * its alpha for lerping the fish to the bobber location is set in the DA_FishingRodConfig data asset's CurveFloat assets respectively, can be tweaked to your liking as well.
 *
 * Then the movement of the fish is controlled by the fish's timelines eased by CurveFloat assigned to the DA_FishingRodConfig data asset.
 */
UCLASS()
class FISHINGFEATURE_API AActor_Fish : public AActor, public ICatchableInterface
{
	GENERATED_BODY()

public:
	/*
	 * Default constructor, constructs the necessary fish component and subobjects.
	 */
	AActor_Fish();

#pragma region ICatchableInterface
	/*
	 * Fish can be caught by a fishing rod, this function is called when this is the nearest fish to the fishing rod's bobber location.
	 * The fish will just lerp to the fishing rod's bobber location via timelines eased by CurveFloat assigned to the DA_FishingRodConfig data asset.
	 */
	virtual void ReeledIn(const FVector& RodLocation) override;

	/*
	 * Fish is able to escape when the player is too early reeling out the fishing rod.
	 * The fish will just lerp back to the original location and rotation via timelines eased by CurveFloat assigned to the DA_FishingRodConfig data asset.
	 */
	virtual void Escape() override;

	/*
	 * This function is called when the fish is caught, it will attach the fish to the fishing rod's scene component.
	 */
	virtual void Catch(USceneComponent* InCatchingRod) override;

	/*
	 * Initializes the fish's spawn area center and extent for the fish to randomly swim around.
	 */
	FORCEINLINE virtual void
	SetSpawnAreaCenterAndExtent(const FVector& InCenter, const FVector& InContainingSpawnAreaBoxExtent) override
	{
		ContainingSpawnAreaCenter = InCenter;
		ContainingSpawnAreaBoxExtent = InContainingSpawnAreaBoxExtent;
	}
#pragma endregion

protected:
	/*
	 * Initializes the parameters, timelines and movement values for the fish.
	 */
	virtual void BeginPlay() override;

	/*
	 * Gets the fish's movement values from the DA_ActorFishConfig data asset.
	 */
	void SetupFishMovementValues();

	/*
	 * Drives the fish's random movement around the spawn area and ticks the timelines as well.
	 */
	virtual void Tick(float DeltaSeconds) override;

	/*
	 * The fish's sphere collision component, acts as the root and the fish's collision box when fishing rod is cast.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Fish")
	USphereComponent* FishSphereCollision = nullptr;

	/*
	 * The fish's mesh component, acts as the fish's visual representation.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Fish")
	UStaticMeshComponent* FishMesh = nullptr;

	/*
	 * The fish's data asset, contains the fish's configuration data. Tweak the data asset to your liking.
	 */
	UPROPERTY(EditAnywhere, Category = "Fish | Config")
	UDataAsset_ActorFishConfig* ActorFishConfigData = nullptr;

private:
	/*
	 * Cached fish's initial location, used for the fish to escape when the player is too early reeling out the fishing rod.
	 */
	UPROPERTY(Transient)
	FVector InitialActorLocation = FVector::ZeroVector;

	/*
	 * Cached fish's spawn area extent, used for the fish to randomly swim around via getting random locations inside the extent.
	 */
	UPROPERTY(Transient)
	FVector ContainingSpawnAreaCenter = FVector::ZeroVector;

	/*
	 * Cached fish's spawn area extent, used for the fish to randomly swim around via getting random locations inside the extent.
	 */
	UPROPERTY(Transient)
	FVector ContainingSpawnAreaBoxExtent = FVector::ZeroVector;

	/*
	 * Cached fish's rotation speed from the DA_ActorFishConfig data asset.
	 */
	UPROPERTY(Transient)
	float FishRotationSpeed = 0.f;

	/*
	 * Cached fish's move speed from the DA_ActorFishConfig data asset.
	 */
	UPROPERTY(Transient)
	float FishMoveSpeed = 0.f;

	/*
	 * Cached fish's wander target radius from the DA_ActorFishConfig data asset, used to determine if the fish should get a new target location to wander around.
	 */
	UPROPERTY(Transient)
	float FishWanderTargetRadius = 0.f;

	/*
	 * Cached fish's escape rotation, used to interpolate the fish's location and rotation to the escape location and rotation.
	 */
	UPROPERTY(Transient)
	FRotator EscapeRotation = FRotator::ZeroRotator;

	/*
	 * Cached fish's reel in location, used to interpolate the fish's location and rotation to the reel in location and rotation.
	 */
	UPROPERTY(Transient)
	FVector ReelInLocation = FVector::ZeroVector;

	/*
	 * Cached fish's look at reel in rotation, used to interpolate the fish's location and rotation to the reel in location and rotation.
	 */
	UPROPERTY(Transient)
	FRotator LookAtReelInRotation = FRotator::ZeroRotator;

	/*
	 * Whether the fish is being targeted by the fishing rod, if true, the fish will not wander around and will only move to the fishing rod's bobber location.
	 */
	UPROPERTY(Transient)
	bool bBeingTargeted = false;

	/*
	 * Cached fish's wander target location from the DA_ActorFishConfig data asset, used to determine if the fish should wander around.
	 */
	UPROPERTY(Transient)
	FVector WanderTargetLocation = FVector::ZeroVector;

	/*
	 * Cached fish's wander look at target rotation from the DA_ActorFishConfig data asset, used to interpolate the fish's location and rotation to the wander target location and rotation.
	 */
	UPROPERTY(Transient)
	FRotator WanderLookAtTargetRotation = FRotator::ZeroRotator;

	/*
	 * Sets up the fish's timelines and their callbacks along with the curves used for the timelines.
	 */
	void SetupTimelines();

	/*
	 * Drives the fish's random movement around the spawn area, only if the fish is not being targeted.
	 */
	void WanderWithinBoundingBox(float DeltaSeconds);

	/*
	 * Ticks the fish's timelines (reeling in and escaping).
	 */
	void TickTimelines(float DeltaSeconds);

	/*
	 * The fish's reeling in timeline, drives the fish's location and rotation to the reel in location and rotation.
	 */
	UPROPERTY(Transient)
	FTimeline ReeledInTimeline;

	/*
	 * The fish's reeling in timeline's float update callback delegate.
	 */
	FOnTimelineFloat ReeledInFloatUpdate;

	/*
	 * The fish's reeling in timeline's float update callback.
	 */
	UFUNCTION()
	void OnReelInUpdate(float InAlpha);

	/*
	 * The fish's reeling in timeline's finished event callback delegate.
	 */
	FOnTimelineEvent ReeledInFinishedEvent;

	/*
	 * The fish's reeling in timeline's finished event callback.
	 */
	UFUNCTION()
	void OnReelInFinished();

	/*
	 * The fish's escape timeline, drives the fish's location and rotation to the escape location and rotation.
	 */
	UPROPERTY(Transient)
	FTimeline EscapeTimeline;

	/*
	 * The fish's escape timeline's float update callback delegate.
	 */
	FOnTimelineFloat EscapeFloatUpdate;

	/*
	 * The fish's escape timeline's float update callback.
	 */
	UFUNCTION()
	void OnEscapeUpdate(float InAlpha);

	/*
	 * The fish's escape timeline's finished event callback delegate
	 */
	FOnTimelineEvent EscapeFinishedEvent;

	/*
	 * The fish's escape timeline's finished event callback.
	 */
	UFUNCTION()
	void OnEscapeFinished();

	/*
	 * Sets up the timeline's data and callbacks along with the curves used for the timelines.
	 */
	void SetupTimelineDataAndCallbacks(FTimeline* InTimeline, const FOnTimelineFloat& InOnTimelineFloat, const FOnTimelineEvent& InOnTimelineEvent, UCurveFloat* InCurveFloat) const;

	/*
	 * Clears the timeline's data and callbacks when timelines are finished.
	 */
	static void ClearTimeline(FOnTimelineFloat* InTimelineFloat, FOnTimelineEvent* InTimelineEvent);

	/*
	 * Interpolates the fish's location and rotation to the target location and rotation.
	 */
	void InterpolateLocationAndRotation(const FVector& InTargetLocation, const FRotator& InTargetRotation, const float& InAlpha);

	/*
	 * Plays the fish's bite sound when it is reeled in.
	 */
	void PlayBiteSound() const;
};