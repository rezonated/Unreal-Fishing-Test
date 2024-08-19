// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest/FunctionalTest_FishingFeatureTest.h"
#include "FunctionalFishingFeatureTest_ReelTest.generated.h"
/*
 * This class focuses on testing the fishing component's ability to reel in.
 *
 * Validating if the fishing feature data assets variables are set correctly and able to reel in.
 *
 * Can be used to test the scenario where the player is too early to reel in or on time to reel in, see the bExpectedResult variable - can be set to true or false in details panel.
 */
UCLASS()
class FISHINGFEATURETESTS_API AFunctionalFishingFeatureTest_ReelTest : public AFunctionalTest_FishingFeatureTest
{
	GENERATED_BODY()

public:
	/*
	 * Default constructor, allows for the actor to tick.
	 */
	AFunctionalFishingFeatureTest_ReelTest();

protected:
	/*
	 * Attempts to find the fishing component to mock, getting the randomized fishing values and binding necessary delegates because we need to know if the reel in is done and if the bobber lands on water.
	 */
	virtual void BeginPlay() override;

	/*
	 * Cleans up the mock reel in delegate binding.
	 */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/*
	 * Used to simulate hold down LMB for the fishing component to cast.
	 */
	virtual void Tick(float DeltaTime) override;

	/*
	 * Cleans up the mock reel in delegate binding.
	 */
	void CleanupMockReelInDelegateBinding();

	/*
	 * Handles the mock reel in done delegate.
	 */
	void OnMockReelInDone(const bool& bSuccess);

	/*
	 * Handles the bobber lands on water delegate.
	 */
	void OnBobberLandsOnWater(const bool&) const;

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
	 * Cached randomized mock reel in time.
	 */
	UPROPERTY(Transient)
	float RandomizedMockReelInTime = 0.0f;

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

	/*
	 * Minimum mock reel in time to randomize the mock reel in time.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MinMockReelInTime = 1.0f;

	/*
	 * Maximum mock reel in time to randomize the mock reel in time.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MaxMockReelInTime = 3.0f;

	/*
	 * Expected result of the reel in test, can be set to true or false in details panel to simulate the scenario where the player is too early to reel in or on time to reel in.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	bool bExpectedResult = true;
};
