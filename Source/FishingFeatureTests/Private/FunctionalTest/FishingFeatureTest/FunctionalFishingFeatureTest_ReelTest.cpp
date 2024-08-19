// Vanan Andreas - 2024


#include "FunctionalTest/FishingFeatureTest/FunctionalFishingFeatureTest_ReelTest.h"

#include "Interface/MockableFishingInterface.h"


AFunctionalFishingFeatureTest_ReelTest::AFunctionalFishingFeatureTest_ReelTest()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFunctionalFishingFeatureTest_ReelTest::BeginPlay()
{
	Super::BeginPlay();
	
	if (!PrepLookForMockableFishingComponent())
	{
		return;
	}
	
	RandomizedMockFishingTime = FMath::FRandRange(MinMockHoldFishingTime, MaxMockHoldFishingTime);

	RandomizedMockReelInTime = FMath::FRandRange(MinMockReelInTime, MaxMockReelInTime);

	CurrentFishingComponentToMock->OnMockReelInDone().BindUObject(this, &ThisClass::OnMockReelInDone);

	CurrentFishingComponentToMock->OnMockBobberLandsOnWater().BindUObject(this, &ThisClass::OnBobberLandsOnWater);
}

void AFunctionalFishingFeatureTest_ReelTest::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CleanupMockReelInDelegateBinding();
	
	Super::EndPlay(EndPlayReason);
}

void AFunctionalFishingFeatureTest_ReelTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentFishingComponentToMock)
	{
		return;
	}

	if (CurrentMockFishingTime <= RandomizedMockFishingTime)
	{
		CurrentMockFishingTime += DeltaTime;
		CurrentFishingComponentToMock->MockCast(CurrentMockFishingTime);
	
		if (CurrentMockFishingTime >= RandomizedMockFishingTime)
		{
			CurrentFishingComponentToMock->MockCastEnd();
		}
	}
}

void AFunctionalFishingFeatureTest_ReelTest::CleanupMockReelInDelegateBinding()
{
	if (CurrentFishingComponentToMock)
	{
		CurrentFishingComponentToMock->OnMockReelInDone().Unbind();
		CurrentFishingComponentToMock->OnMockBobberLandsOnWater().Unbind();
		
		CurrentFishingComponentToMock = nullptr;
	}
}

void AFunctionalFishingFeatureTest_ReelTest::OnMockReelInDone(const bool& bSuccess)
{
	const EFunctionalTestResult FunctionalTestResult = bSuccess == bExpectedResult ? EFunctionalTestResult::Succeeded : EFunctionalTestResult::Failed;
	const FString Message = bSuccess == bExpectedResult ? TEXT("Mocking reel in component succeeded") : TEXT("Mocking reel in component failed");

	FinishTest(FunctionalTestResult, Message);
}

void AFunctionalFishingFeatureTest_ReelTest::OnBobberLandsOnWater(const bool&) const
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this] {
		bExpectedResult ? CurrentFishingComponentToMock->MockCast(0.f) : CurrentFishingComponentToMock->MockCastEnd();
	}, RandomizedMockReelInTime, false);
}

