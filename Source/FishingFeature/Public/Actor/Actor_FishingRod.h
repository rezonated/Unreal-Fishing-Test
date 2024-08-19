// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/CatcherInterface.h"
#include "Actor_FishingRod.generated.h"

class UDataAsset_FishingRodConfig;

/*
 * Fishing rod actor class, handles fishing rod movement and able to be thrown into the water and lands on the water.
 *
 * It has scene components for the bobber and the catchable attach point for fish to attach to, the fishing rod config data asset is used to set up the fishing rod's movement values. Tweak the data asset to your liking.
 * 
 * The fishing rod can be toggled to be visible or invisible via the toggle bobber and toggle catcher visibility functions.
 * Useful for when we're in the ShowFish state and don't want the fishing rod to be visible.
 * 
 * The movement of fishing rod for throwing and pulling is controlled by the fishing rod's timelines eased by CurveFloat assigned to the DA_FishingRodConfig data asset.
 */
UCLASS()
class FISHINGFEATURE_API AActor_FishingRod : public AActor, public ICatcherInterface
{
	GENERATED_BODY()

public:
	/*
	 * Default constructor, constructs the subobjects and components necessary.
	 */
	AActor_FishingRod();

#pragma region ICatcherInterface
	/*
	 * Fishing rod can be thrown by the player to the location provided by the parameter.
	 */
	virtual void Throw(const FVector& InCastLocation) override;

	/*
	 * Fishing rod's bobber can be reeled back to the initial location and rotation.
	 */
	virtual void ReelBack() override;

	/*
	 * Delegate for when the fishing rod lands on the water.
	 */
	FORCEINLINE virtual FSimpleDelegate& OnLandsOnWater() override { return CatchableLandsOnWaterDelegate; }

	/*
	 * Catchable attach point for the fish to attach to.
	 */
	FORCEINLINE virtual USceneComponent* GetCatchableAttachPoint() override { return CatchableAttachPoint; }

	/*
	 * Toggles the fishing rod's bobber visibility.
	 */
	virtual void ToggleBobberVisibility(const bool& bInShouldBeVisible) override;

	/*
	 * Toggles the fishing rod's visibility.
	 */
	virtual void ToggleCatcherVisibility(const bool& bInShouldBeVisible) override;
#pragma endregion

protected:
	/*
	 * Sets up the fishing rod's timelines and their callbacks along with the curves used for the timelines, also caching the fishing rod's initial bobber location for reeling back purposes.
	 */
	virtual void BeginPlay() override;

	/*
	 * Ticks the fishing rod's timelines (throw and pull).
	 */
	virtual void Tick(float DeltaSeconds) override;

	/*
	 * The fishing rod's mesh component, acts as the fishing rod's visual representation.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* FishingRodMeshComponent = nullptr;

	/*
	 * The fishing rod's bobber mesh component, acts as the fishing rod's bobber visual representation.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BobberMeshComponent = nullptr;

	/*
	 * The fishing rod's catchable attach point, acts as the fishing rod's catchable attach point for the fish to attach to.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* CatchableAttachPoint = nullptr;

	/*
	 * The fishing rod's data asset, contains the fishing rod's configuration data. Tweak the data asset to your liking.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Bobber Curve")
	UDataAsset_FishingRodConfig* FishingRodConfigData = nullptr;

	/*
	 * Cached fishing rod's bobber target location, assigned from the Throw interface implementation. Will be used for the fishing rod's timelines.
	 */
	UPROPERTY(Transient)
	FVector BobberTargetLocation = FVector::ZeroVector;

	/*
	 * Cached fishing rod's bobber start location, assigned from the Throw interface implementation. Will be used for the fishing rod's pull timeline.
	 */
	UPROPERTY(Transient)
	FVector BobberStartLocation = FVector::ZeroVector;

	/*
	 * Sets up the timelines and their callbacks along with the curves used for the timelines.
	 */
	void SetupTimelines();

	/*
	 * Ticks the fishing rod's timelines (throw and pull).
	 */
	void TickTimelines(float DeltaSeconds);

	/*
	 * Sets up the fishing rod's timelines' data and callbacks along with the curves used for the timelines.
	 */
	void SetupTimelineDataAndCallbacks(FTimeline* InTimeline, const FOnTimelineFloat& InOnTimelineFloat, const FOnTimelineEvent& InOnTimelineEvent, UCurveFloat* InCurveFloat) const;

	/*
	 * Clears the fishing rod's timelines' data and callbacks when timelines are finished.
	 */
	static void ClearTimeline(FOnTimelineFloat* InTimelineFloat, FOnTimelineEvent* InTimelineEvent);

	/*
	 * The fishing rod's throw timeline, drives the fishing rod's location and rotation to the fishing rod's bobber location.
	 */
	UPROPERTY(Transient)
	FTimeline ThrowReelInTimeline;

	/*
	 * The fishing rod's throw timeline's float update callback delegate.
	 */
	FOnTimelineFloat ThrowReelInFloatUpdate;

	/*
	 * The fishing rod's throw timeline's float update callback.
	 */
	UFUNCTION()
	void OnThrowReelInUpdate(float InAlpha);

	/*
	 * The fishing rod's throw timeline's finished event callback delegate.
	 */
	FOnTimelineEvent ThrowReelInFinishedEvent;

	/*
	 * The fishing rod's throw timeline's finished event callback.
	 */
	UFUNCTION()
	void OnThrowReelInFinished();

	/*
	 * The fishing rod's pull timeline, drives the fishing rod's location and rotation to the fishing rod's bobber location.
	 */
	UPROPERTY(Transient)
	FTimeline PullReelOutTimeline;

	/*
	 * The fishing rod's pull timeline's float update callback delegate.
	 */
	FOnTimelineFloat PullReelOutFloatUpdate;

	/*
	 * The fishing rod's pull timeline's float update callback.
	 */
	UFUNCTION()
	void OnPullReelOutUpdate(float InAlpha);

	/*
	 * The fishing rod's pull timeline's finished event callback delegate.
	 */
	FOnTimelineEvent PullReelOutFinishedEvent;

	/*
	 * The fishing rod's pull timeline's finished event callback.
	 */
	UFUNCTION()
	void OnPullReelOutFinished();

	/*
	 * Interpolates the fishing rod's bobber location to the fishing rod's bobber target location.
	 */
	void InterpolateBobberLocation(const float& InAlpha) const;

	/*
	 * Delegate for when the fishing rod lands on the water, used as return value for the CatchableLandsOnWater interface function implementation.
	 */
	FSimpleDelegate CatchableLandsOnWaterDelegate;
};