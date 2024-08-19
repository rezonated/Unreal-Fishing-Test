// Vanan Andreas - 2024

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class FISHINGGAMEPLAYTAGS_API FFishingTags : public FNoncopyable
{
public:
	static void Startup(UGameplayTagsManager& GameplayTagsManager);

	static FORCEINLINE FFishingTags& Get()
	{
		static FFishingTags FishingTags;
		return FishingTags;
	}

	FGameplayTag Messaging_Fishing_UI_Cast_Update;

	FGameplayTag Messaging_Fishing_Notify_Throw;
	FGameplayTag Messaging_Fishing_Notify_ReelDone;

	FGameplayTag Messaging_Fishing_AnimInstance_StateChange;

	FGameplayTag Messaging_GameState_StateChange;

	FGameplayTag Messaging_GameMode_StateChangeFinish;

	FGameplayTag AnimInstance_Fishing_State_Idling;
	FGameplayTag AnimInstance_Fishing_State_Throwing;
	FGameplayTag AnimInstance_Fishing_State_Reeling_In;
	FGameplayTag AnimInstance_Fishing_State_Reeling_Out;
	FGameplayTag AnimInstance_Fishing_State_ShowFish;

	FGameplayTag FishingComponent_State_Idling;
	FGameplayTag FishingComponent_State_Throwing;
	FGameplayTag FishingComponent_State_WaitingForFish;
	FGameplayTag FishingComponent_State_AbleToReel;
	FGameplayTag FishingComponent_State_Reeling_In;
	FGameplayTag FishingComponent_State_Reeling_Out;

	FGameplayTag FishingGameLoopState_Fishing;
	FGameplayTag FishingGameLoopState_ShowFish;
};