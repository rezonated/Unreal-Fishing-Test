// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest/FunctionalTest_FishingFeatureTest.h"
#include "FunctionalFishingFeatureTest_ReelTest.generated.h"

UCLASS()
class FISHINGFEATURETESTS_API AFunctionalFishingFeatureTest_ReelTest : public AFunctionalTest_FishingFeatureTest
{
	GENERATED_BODY()

public:
	AFunctionalFishingFeatureTest_ReelTest();

protected:
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void Tick(float DeltaTime) override;

	void CleanupMockReelInDelegateBinding();
	
	void OnMockReelInDone(const bool& bSuccess);

	void OnBobberLandsOnWater(const bool&) const;

	UPROPERTY(Transient)
	float CurrentMockFishingTime = 0.0f;

	UPROPERTY(Transient)
	float RandomizedMockFishingTime = 0.0f;

	UPROPERTY(Transient)
	float RandomizedMockReelInTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MinMockHoldFishingTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MaxMockHoldFishingTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MinMockReelInTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	float MaxMockReelInTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functional Testing", meta=(AllowPrivateAccess=true))
	bool bExpectedResult = true;
};
