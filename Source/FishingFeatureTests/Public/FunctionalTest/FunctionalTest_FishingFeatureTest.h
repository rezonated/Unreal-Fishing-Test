// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "FunctionalTest_FishingFeatureTest.generated.h"

class IMockableFishingInterface;

/*
 * Functional test for fishing feature.
 * Focuses to test the fishing component by interacting with the IMockableFishingInterface interface.
 */
UCLASS()
class FISHINGFEATURETESTS_API AFunctionalTest_FishingFeatureTest : public AFunctionalTest
{
	GENERATED_BODY()

public:
	/*
	 * Default constructor, allows for the actor to tick.
	 */
	AFunctionalTest_FishingFeatureTest();

	/*
	 * Attempts to find the fishing component to mock.
	 */
	bool PrepLookForMockableFishingComponent();

protected:
	virtual void Tick(float DeltaSeconds) override;

	/*
	 * Finishes the test with the given result and message and added quit game after finishing the test.
	 */
	virtual void FinishTest(EFunctionalTestResult TestResult, const FString& Message) override;

	/*
	 * Cached fishing component to mock.
	 */
	IMockableFishingInterface* CurrentFishingComponentToMock = nullptr;
};
