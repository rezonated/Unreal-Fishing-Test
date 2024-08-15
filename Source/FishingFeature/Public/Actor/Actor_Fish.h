// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/CatchableInterface.h"
#include "Actor_Fish.generated.h"

class UDataAsset_ActorFishConfig;
class USphereComponent;

UCLASS()
class FISHINGFEATURE_API AActor_Fish : public AActor, public ICatchableInterface
{
	GENERATED_BODY()

	template<class UserClass, typename RetValType, typename... ParamTypes>
	class TFunctionAddressResolver
	{
	public:
		typedef RetValType (UserClass::*FMethodPtr)(ParamTypes... Params);
	};

public:
	AActor_Fish();
	
	virtual void ReeledIn(const FVector& RodLocation) override;
	virtual void Escape() override;
	virtual void Catch() override {}
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Fish")
	USphereComponent* FishSphereCollision = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Fish")
	UStaticMeshComponent* FishMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Fish | Config")
	UDataAsset_ActorFishConfig* ActorFishConfigData = nullptr;
	
private:
	UPROPERTY(Transient)
	FVector InitialActorLocation = FVector::ZeroVector;

	UPROPERTY(Transient)
	FRotator EscapeRotation = FRotator::ZeroRotator;

	UPROPERTY(Transient)
	FVector ReelInLocation = FVector::ZeroVector;

	UPROPERTY(Transient)
	FRotator LookAtReelInRotation = FRotator::ZeroRotator;

	UPROPERTY(Transient)
	FTimeline ReelInTimeline;

	void SetupTimelines();
	
	FOnTimelineFloat ReelInFloatUpdate;
	UFUNCTION()
	void OnReelInUpdate(float InAlpha);

	FOnTimelineEvent ReelInFinishedEvent;
	UFUNCTION()
	void OnReelInFinished();

	UPROPERTY(Transient)
	FTimeline EscapeTimeline;

	FOnTimelineFloat EscapeFloatUpdate;
	UFUNCTION()
	void OnEscapeUpdate(float InAlpha);

	FOnTimelineEvent EscapeFinishedEvent;
	UFUNCTION()
	void OnEscapeFinished();

	void SetupTimelineDataAndCallbacks(FTimeline* InTimeline, const FOnTimelineFloat& InOnTimelineFloat, const FOnTimelineEvent& InOnTimelineEvent, UCurveFloat* InCurveFloat) const;

	static void ClearTimeline(FOnTimelineFloat* InTimelineFloat, FOnTimelineEvent* InTimelineEvent);

	void InterpolateLocationAndRotation(const FVector& InTargetLocation, const FRotator& InTargetRotation, const float& InAlpha);
};