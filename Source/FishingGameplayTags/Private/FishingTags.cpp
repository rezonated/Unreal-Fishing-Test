// Vanan Andreas - 2024


#include "FishingTags.h"

#include "GameplayTagsManager.h"

void FFishingTags::Startup(UGameplayTagsManager& GameplayTagsManager)
{
	FFishingTags& FishingTags = Get();

	FishingTags.Messaging_Fishing_UI_Cast_Update = GameplayTagsManager.AddNativeGameplayTag(TEXT("Messaging.Fishing.UI.Cast.Update"));

	FishingTags.Messaging_Fishing_Notify_Throw = GameplayTagsManager.AddNativeGameplayTag(TEXT("Messaging.Fishing.Notify.Throw"));
	FishingTags.Messaging_Fishing_Notify_ReelDone = GameplayTagsManager.AddNativeGameplayTag(TEXT("Messaging.Fishing.Notify.ReelDone"));

	FishingTags.Messaging_Fishing_AnimInstance_StateChange = GameplayTagsManager.AddNativeGameplayTag(TEXT("Messaging.Fishing.AnimInstance.StateChange"));

	FishingTags.Messaging_GameState_StateChange = GameplayTagsManager.AddNativeGameplayTag(TEXT("Messaging.GameState.StateChange"));

	FishingTags.Messaging_GameMode_StateChangeFinish = GameplayTagsManager.AddNativeGameplayTag(TEXT("Messaging.GameMode.StateChange.Finish"));

	FishingTags.AnimInstance_Fishing_State_Idling = GameplayTagsManager.AddNativeGameplayTag(TEXT("AnimInstance.Fishing.State.Idling"));
	FishingTags.AnimInstance_Fishing_State_Throwing = GameplayTagsManager.AddNativeGameplayTag(TEXT("AnimInstance.Fishing.State.Throwing"));
	FishingTags.AnimInstance_Fishing_State_Reeling_In = GameplayTagsManager.AddNativeGameplayTag(TEXT("AnimInstance.Fishing.State.Reeling.In"));
	FishingTags.AnimInstance_Fishing_State_Reeling_Out = GameplayTagsManager.AddNativeGameplayTag(TEXT("AnimInstance.Fishing.State.Reeling.Out"));
	FishingTags.AnimInstance_Fishing_State_ShowFish = GameplayTagsManager.AddNativeGameplayTag(TEXT("AnimInstance.Fishing.State.ShowFish"));

	FishingTags.FishingComponent_State_Idling = GameplayTagsManager.AddNativeGameplayTag(TEXT("FishingComponent.State.Idling"));
	FishingTags.FishingComponent_State_Throwing = GameplayTagsManager.AddNativeGameplayTag(TEXT("FishingComponent.State.Throwing"));
	FishingTags.FishingComponent_State_WaitingForFish = GameplayTagsManager.AddNativeGameplayTag(TEXT("FishingComponent.State.WaitingForFish"));
	FishingTags.FishingComponent_State_AbleToReel = GameplayTagsManager.AddNativeGameplayTag(TEXT("FishingComponent.State.AbleToReel"));
	FishingTags.FishingComponent_State_Reeling_In = GameplayTagsManager.AddNativeGameplayTag(TEXT("FishingComponent.State.Reeling.In"));
	FishingTags.FishingComponent_State_Reeling_Out = GameplayTagsManager.AddNativeGameplayTag(TEXT("FishingComponent.State.Reeling.Out"));

	FishingTags.FishingGameLoopState_Fishing = GameplayTagsManager.AddNativeGameplayTag(TEXT("FishingGameLoopState.Fishing"));
	FishingTags.FishingGameLoopState_ShowFish = GameplayTagsManager.AddNativeGameplayTag(TEXT("FishingGameLoopState.ShowFish"));
}