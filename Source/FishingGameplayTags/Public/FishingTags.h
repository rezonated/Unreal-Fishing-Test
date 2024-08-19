// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/*
 * This class contains all the fishing gameplay tags used in the game.
 *
 * Inherits from the FNoncopyable class to prevent the class from being copied due to this being a singleton class, we don't want another instance of this class - just this one instance.
 *
 * Accessing the necessary native gameplay tags is done via the Get() function, which returns a reference to the FFishingTags singleton instance - then we can access the gameplay tags via the dot operator.
 *
 * Having this class is necessary because we would like to inject the fishing gameplay tags into the gameplay tags manager, which is done via the Startup() function - called from the startup module that listens OnLastChanceToAddNativeTags event and registers these fishing native tags to the gameplay tags manager.
 */
class FISHINGGAMEPLAYTAGS_API FFishingTags : public FNoncopyable
{
public:
	/*
	 * Sets up the fishing gameplay tags to the gameplay tags manager.
	 */
	static void Startup(UGameplayTagsManager& GameplayTagsManager);

	/*
	 * Returns the fishing gameplay tags singleton instance as a reference.
	 */
	static FORCEINLINE FFishingTags& Get()
	{
		static FFishingTags FishingTags;
		return FishingTags;
	}

	/*
	 * Messaging tag for fishing UI cast update.
	 */
	FGameplayTag Messaging_Fishing_UI_Cast_Update;

	/*
	 * Messaging tag for fishing notify throw.
	 */
	FGameplayTag Messaging_Fishing_Notify_Throw;

	/*
	 * Messaging tag for fishing notify reel done.
	 */
	FGameplayTag Messaging_Fishing_Notify_ReelDone;

	/*
	 * Messaging tag for fishing anim instance state change.
	 */
	FGameplayTag Messaging_Fishing_AnimInstance_StateChange;

	/*
	 * Messaging tag for game state state change.
	 */
	FGameplayTag Messaging_GameState_StateChange;

	/*
	 * Messaging tag for game mode state change finish.
	 */
	FGameplayTag Messaging_GameMode_StateChangeFinish;

	/*
	 * Anim instance tag for fishing state idling, used for playing appropriate anim montage.
	 */
	FGameplayTag AnimInstance_Fishing_State_Idling;

	/*
	 * Anim instance tag for fishing state throwing, used for playing appropriate anim montage.
	 */
	FGameplayTag AnimInstance_Fishing_State_Throwing;

	/*
	 * Anim instance tag for fishing state reeling in, used for playing appropriate anim montage.
	 */
	FGameplayTag AnimInstance_Fishing_State_Reeling_In;

	/*
	 * Anim instance tag for fishing state reeling out, used for playing appropriate anim montage.
	 */
	FGameplayTag AnimInstance_Fishing_State_Reeling_Out;

	/*
	 * Anim instance tag for fishing state show fish, used for playing appropriate anim montage.
	 */
	FGameplayTag AnimInstance_Fishing_State_ShowFish;

	/*
	 * Fishing component tag for fishing component state idling, used for handling internal state inside the fishing component.
	 */
	FGameplayTag FishingComponent_State_Idling;

	/*
	 * Fishing component tag for fishing component state throwing, used for handling internal state inside the fishing component.
	 */
	FGameplayTag FishingComponent_State_Throwing;

	/*
	 * Fishing component tag for fishing component state waiting for fish, used for handling internal state inside the fishing component.
	 */
	FGameplayTag FishingComponent_State_WaitingForFish;

	/*
	 * Fishing component tag for fishing component state able to reel, used for handling internal state inside the fishing component.
	 */
	FGameplayTag FishingComponent_State_AbleToReel;

	/*
	 * Fishing component tag for fishing component state reeling in, used for handling internal state inside the fishing component.
	 */
	FGameplayTag FishingComponent_State_Reeling_In;

	/*
	 * Fishing component tag for fishing component state reeling out, used for handling internal state inside the fishing component.
	 */
	FGameplayTag FishingComponent_State_Reeling_Out;

	/*
	 * Fishing game loop state tag for fishing game loop state fishing, used for handling the fishing game loop state.
	 */
	FGameplayTag FishingGameLoopState_Fishing;

	/*
	 * Fishing game loop state tag for fishing game loop state show fish, used for handling the fishing game loop state.
	 */
	FGameplayTag FishingGameLoopState_ShowFish;
};