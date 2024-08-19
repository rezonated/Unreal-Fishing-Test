// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest/FunctionalTest_FishingFeatureTest.h"
#include "FunctionalFishingFeatureTest_AbleToCatchFish.generated.h"

/*
 * This class focuses on testing the fishing component's ability to catch fish.
 * Validating if the fishing feature data assets variables are set correctly and able to catch fish.
 */
UCLASS()
class FISHINGFEATURETESTS_API AFunctionalFishingFeatureTest_AbleToCatchFish : public AFunctionalTest_FishingFeatureTest
{
	GENERATED_BODY()

public:
	/*
	 * Default constructor, allows for the actor to tick.
	 */
	AFunctionalFishingFeatureTest_AbleToCatchFish();

protected:
	/*
	 * Attempts to find the fishing component to mock, getting the randomized fishing time and binding the mock able to catch fish
	 * done delegate because we need to know if the fishing component is able to detect fish and get a nearest one.
	 */
	virtual void BeginPlay() override;

	/*
	 * Used to simulate hold down LMB for the fishing component to cast.
	 */
	virtual void Tick(float DeltaSeconds) override;

	/*
	 * Handles the mock able to catch fish done delegate.
	 */
	void OnMockAbleToCatchFishDone(const bool& bSuccess);

	/*
	 * Cleans up the mock able to catch fish delegate binding.
	 */
	void CleanupMockAbleToCatchFishDelegateBinding();

private:
	/*
	 * Cached current mock fishing time.
	 */
	UPROPERTY(Transient)
	float CurrentMockFishingTime = 0.0f;

	/*
	 * Cached randomized mock fishing time.
	 */
	UPROPERTY(Transient)
	float RandomizedMockFishingTime = 0.0f;

	/*
	 * Minimum mock fishing time to randomize the mock LMB hold fishing time.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MinMockHoldFishingTime = 1.0f;

	/*
	 * Maximum mock fishing time to randomize the mock LMB hold fishing time.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MaxMockHoldFishingTime = 3.0f;
};
