// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest/FunctionalTest_FishingFeatureTest.h"
#include "FunctionalFishingFeatureTest_AbleToCatchFish.generated.h"

UCLASS()
class FISHINGFEATURETESTS_API AFunctionalFishingFeatureTest_AbleToCatchFish : public AFunctionalTest_FishingFeatureTest
{
	GENERATED_BODY()

public:
	AFunctionalFishingFeatureTest_AbleToCatchFish();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void OnMockAbleToCatchFishDone(const bool& bSuccess);

	void CleanupMockAbleToCatchFishDelegateBinding();

private:
	UPROPERTY(Transient)
	float CurrentMockFishingTime = 0.0f;

	UPROPERTY(Transient)
	float RandomizedMockFishingTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MinMockHoldFishingTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MaxMockHoldFishingTime = 3.0f;
};
