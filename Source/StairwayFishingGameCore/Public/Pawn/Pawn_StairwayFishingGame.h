// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/SwitchableFishingViewInterface.h"
#include "Pawn_StairwayFishingGame.generated.h"

class UActorComponent_FishingComponent;
class UWidgetComponent;
class UCameraComponent;
class USpringArmComponent;
class UArrowComponent;
class UCapsuleComponent;

/*
 * Pawn used for the game. Handles the necessary components and switching the fishing view - thus implementing the ISwitchableFishingViewInterface interface.
 *
 * Uses pawn instead of character due to no movement input needed.
 */
UCLASS()
class STAIRWAYFISHINGGAMECORE_API APawn_StairwayFishingGame : public APawn, public ISwitchableFishingViewInterface
{
	GENERATED_BODY()

public:
	/*
	 * Default constructor, disables the ticking.
	 */
	APawn_StairwayFishingGame();

	/*
	 * Enables the camera and disables the other based on the given fishing game loop state.
	 */
	virtual void SetFishingView(const FGameplayTag& InFishingGameLoopStateTag) override;

protected:
	/*
	 * Capsule component for the fishing pawn, used for root.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UCapsuleComponent* Capsule = nullptr;

	/*
	 * Skeletal mesh component for the fishing pawn, visual representation of the pawn.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	USkeletalMeshComponent* Mesh = nullptr;

	/*
	 * Arrow component for the fishing pawn, for debug purposes.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UArrowComponent* Arrow = nullptr;

	/*
	 * Spring arm component for the fishing pawn, to attach the top down camera to.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	USpringArmComponent* SpringArm = nullptr;

	/*
	 * Actual top down camera component for the fishing pawn. By default, this camera is enabled.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UCameraComponent* Camera = nullptr;

	/*
	 * Cast meter bar widget for the fishing pawn, used for showing the cast meter based on how long the player has held LMB.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UWidgetComponent* CastMeterBarWidget = nullptr;

	/*
	 * Fishing component actor component for the fishing pawn, handles the fishing logic.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UActorComponent_FishingComponent* FishingComponent = nullptr;

	/*
	 * Camera component for the fishing pawn, used for showing the fish. By default, this camera is disabled.
	 */
	UPROPERTY(VisibleAnywhere, Category = "Stairway Fishing Game Pawn")
	UCameraComponent* ShowFishCamera = nullptr;
};