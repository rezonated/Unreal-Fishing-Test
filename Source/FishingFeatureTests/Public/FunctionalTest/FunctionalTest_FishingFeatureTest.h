// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "FunctionalTest_FishingFeatureTest.generated.h"

class IMockableFishingInterface;

UCLASS()
class FISHINGFEATURETESTS_API AFunctionalTest_FishingFeatureTest : public AFunctionalTest
{
	GENERATED_BODY()

public:
	AFunctionalTest_FishingFeatureTest();
	
	bool PrepLookForMockableFishingComponent();

protected:
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void FinishTest(EFunctionalTestResult TestResult, const FString& Message) override;

	IMockableFishingInterface* CurrentFishingComponentToMock = nullptr;
};
