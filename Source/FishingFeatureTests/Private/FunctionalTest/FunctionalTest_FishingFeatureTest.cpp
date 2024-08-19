// Vanan Andreas - 2024


#include "FunctionalTest/FunctionalTest_FishingFeatureTest.h"

#include "Interface/MockableFishingInterface.h"
#include "Kismet/KismetSystemLibrary.h"


AFunctionalTest_FishingFeatureTest::AFunctionalTest_FishingFeatureTest()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool AFunctionalTest_FishingFeatureTest::PrepLookForMockableFishingComponent()
{
	bool bReturnValue = false;
	
	const UWorld* World = GetWorld();
	if (!World)
	{
		FinishTest(EFunctionalTestResult::Failed, "No world found");
		return bReturnValue;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController)
	{
		FinishTest(EFunctionalTestResult::Failed, "No player controller found");
		return bReturnValue;
	}

	PlayerController->DisableInput(PlayerController);

	const APawn* Pawn = PlayerController->GetPawn();
	if (!Pawn)
	{
		FinishTest(EFunctionalTestResult::Failed, "No pawn found");
		return bReturnValue;
	}

	TSet<UActorComponent*> PawnComponents = Pawn->GetComponents();
	if (PawnComponents.Num() <= 0)
	{
		FinishTest(EFunctionalTestResult::Failed, "Pawn has no components");
		return bReturnValue;
	}
	
	for (UActorComponent* Component : PawnComponents)
	{
		if (Component->Implements<UMockableFishingInterface>())
		{
			CurrentFishingComponentToMock = Cast<IMockableFishingInterface>(Component);
			if (!CurrentFishingComponentToMock)
			{
				FinishTest(EFunctionalTestResult::Failed, "Pawn has a component that doesn't implement UFishingFeature");
				return bReturnValue;
			}
		}
	}

	if (CurrentFishingComponentToMock == nullptr)
	{
		FinishTest(EFunctionalTestResult::Failed, "No fishing component found");
		return bReturnValue;
	}

	bReturnValue = true;
	return bReturnValue;
}

void AFunctionalTest_FishingFeatureTest::BeginPlay()
{
	Super::BeginPlay();

	if (!PrepLookForMockableFishingComponent())
	{
		return;
	}

	RandomizedMockFishingTime = FMath::FRandRange(MinMockHoldFishingTime, MaxMockHoldFishingTime);

	CurrentFishingComponentToMock->OnMockDone().BindUObject(this, &ThisClass::OnMockDone);
}

void AFunctionalTest_FishingFeatureTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!CurrentFishingComponentToMock)
	{
		return;
	}

	CurrentMockFishingTime += DeltaSeconds;
	CurrentFishingComponentToMock->MockCast(CurrentMockFishingTime);
	
	if (CurrentMockFishingTime >= RandomizedMockFishingTime)
	{
		CurrentFishingComponentToMock->MockCastEnd();
		CurrentMockFishingTime = 0.0f;
	}
}

void AFunctionalTest_FishingFeatureTest::FinishTest(EFunctionalTestResult TestResult, const FString& Message)
{
	Super::FinishTest(TestResult, Message);

	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void AFunctionalTest_FishingFeatureTest::CleanupMockDelegateBinding()
{
	if (CurrentFishingComponentToMock)
	{
		CurrentFishingComponentToMock->OnMockDone().Unbind();
		
		CurrentFishingComponentToMock = nullptr;
	}
}

void AFunctionalTest_FishingFeatureTest::OnMockDone(const bool& bSuccess)
{
	const EFunctionalTestResult FunctionalTestResult = bSuccess ? EFunctionalTestResult::Succeeded : EFunctionalTestResult::Failed;
	const FString Message = bSuccess ? TEXT("Mocking fishing component succeeded") : TEXT("Mocking fishing component failed");

	CleanupMockDelegateBinding();
	
	FinishTest(FunctionalTestResult, Message);
}
