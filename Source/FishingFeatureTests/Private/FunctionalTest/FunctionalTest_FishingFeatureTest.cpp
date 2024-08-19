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
		if (!Component->Implements<UMockableFishingInterface>())
		{
			continue;
		}
		CurrentFishingComponentToMock = Cast<IMockableFishingInterface>(Component);
		if (!CurrentFishingComponentToMock)
		{
			FinishTest(EFunctionalTestResult::Failed, "Pawn has a component that doesn't implement UFishingFeature");
			return bReturnValue;
		}
		break;
	}

	if (CurrentFishingComponentToMock == nullptr)
	{
		FinishTest(EFunctionalTestResult::Failed, "No fishing component found");
		return bReturnValue;
	}

	bReturnValue = true;
	return bReturnValue;
}

void AFunctionalTest_FishingFeatureTest::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AFunctionalTest_FishingFeatureTest::FinishTest(EFunctionalTestResult TestResult, const FString& Message)
{
	Super::FinishTest(TestResult, Message);

	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
