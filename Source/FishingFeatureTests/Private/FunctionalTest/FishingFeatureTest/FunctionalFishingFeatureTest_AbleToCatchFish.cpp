// Vanan Andreas - 2024


#include "FunctionalTest/FishingFeatureTest/FunctionalFishingFeatureTest_AbleToCatchFish.h"

#include "Interface/MockableFishingInterface.h"


AFunctionalFishingFeatureTest_AbleToCatchFish::AFunctionalFishingFeatureTest_AbleToCatchFish()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFunctionalFishingFeatureTest_AbleToCatchFish::BeginPlay()
{
	Super::BeginPlay();

	if (!PrepLookForMockableFishingComponent())
	{
		return;
	}

	RandomizedMockFishingTime = FMath::FRandRange(MinMockHoldFishingTime, MaxMockHoldFishingTime);

	CurrentFishingComponentToMock->OnMockAbleToCatchFishDone().BindUObject(this, &ThisClass::OnMockAbleToCatchFishDone);
}

void AFunctionalFishingFeatureTest_AbleToCatchFish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!CurrentFishingComponentToMock)
	{
		return;
	}

	CurrentMockFishingTime += DeltaTime;
	CurrentFishingComponentToMock->MockCast(CurrentMockFishingTime);
	
	if (CurrentMockFishingTime >= RandomizedMockFishingTime)
	{
		CurrentFishingComponentToMock->MockCastEnd();
		CurrentMockFishingTime = 0.0f;
	}
}

void AFunctionalFishingFeatureTest_AbleToCatchFish::OnMockAbleToCatchFishDone(const bool& bSuccess)
{
	const EFunctionalTestResult FunctionalTestResult = bSuccess ? EFunctionalTestResult::Succeeded : EFunctionalTestResult::Failed;
	const FString Message = bSuccess ? TEXT("Mocking fishing component succeeded") : TEXT("Mocking fishing component failed");

	CleanupMockAbleToCatchFishDelegateBinding();
	
	FinishTest(FunctionalTestResult, Message);
}

void AFunctionalFishingFeatureTest_AbleToCatchFish::CleanupMockAbleToCatchFishDelegateBinding()
{
	if (CurrentFishingComponentToMock)
	{
		CurrentFishingComponentToMock->OnMockAbleToCatchFishDone().Unbind();
		
		CurrentFishingComponentToMock = nullptr;
	}
}

