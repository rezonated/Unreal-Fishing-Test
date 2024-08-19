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
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void FinishTest(EFunctionalTestResult TestResult, const FString& Message) override;
	
	void CleanupMockDelegateBinding();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing")
	float MinMockHoldFishingTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing")
	float MaxMockHoldFishingTime = 3.0f;

private:
	IMockableFishingInterface* CurrentFishingComponentToMock = nullptr;
	
	void OnMockDone(const bool& bSuccess);

	UPROPERTY(Transient)
	float CurrentMockFishingTime = 0.0f;

	UPROPERTY(Transient)
	float RandomizedMockFishingTime = 0.0f;
};
