// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/CatcherInterface.h"
#include "Actor_FishingRod.generated.h"

class UDataAsset_FishingRodConfig;

UCLASS()
class FISHINGFEATURE_API AActor_FishingRod : public AActor, public ICatcherInterface
{
	GENERATED_BODY()

public:
	AActor_FishingRod();

	void PrepareBobberTimeline(UCurveFloat* InReelCurve);
	
	virtual void Throw(const FVector& InCastLocation) override;
	
	virtual void ReelBack() override;

	FORCEINLINE virtual FSimpleDelegate& OnLandsOnWater() override { return CatchableLandsOnWaterDelegate; }

	FORCEINLINE virtual USceneComponent* GetCatchableAttachPoint() override { return CatchableAttachPoint; }

	virtual void ToggleBobberVisibility(const bool& bInShouldBeVisible) override;

	virtual void ToggleCatcherVisibility(const bool& bInShouldBeVisible) override;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* FishingRodMeshComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BobberMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* CatchableAttachPoint = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Bobber Curve")
	UDataAsset_FishingRodConfig* FishingRodConfigData = nullptr;

	UPROPERTY(Transient)
	FVector BobberTargetLocation = FVector::ZeroVector;

	UPROPERTY(Transient)
	FVector BobberStartLocation = FVector::ZeroVector;
	
	void SetupTimelines();
	void TickTimelines(float DeltaSeconds);

	void SetupTimelineDataAndCallbacks(FTimeline* InTimeline, const FOnTimelineFloat& InOnTimelineFloat, const FOnTimelineEvent& InOnTimelineEvent, UCurveFloat* InCurveFloat) const;

	static void ClearTimeline(FOnTimelineFloat* InTimelineFloat, FOnTimelineEvent* InTimelineEvent);

	UPROPERTY(Transient)
	FTimeline ThrowReelInTimeline;
	
	FOnTimelineFloat ThrowReelInFloatUpdate;
	UFUNCTION()
	void OnThrowReelInUpdate(float InAlpha);

	FOnTimelineEvent ThrowReelInFinishedEvent;
	UFUNCTION()
	void OnThrowReelInFinished();

	UPROPERTY(Transient)
	FTimeline PullReelOutTimeline;

	FOnTimelineFloat PullReelOutFloatUpdate;
	UFUNCTION()
	void OnPullReelOutUpdate(float InAlpha);

	FOnTimelineEvent PullReelOutFinishedEvent;
	UFUNCTION()
	void OnPullReelOutFinished();
	
	void InterpolateBobberLocation
	(const float& InAlpha) const;

	FSimpleDelegate CatchableLandsOnWaterDelegate;
};
