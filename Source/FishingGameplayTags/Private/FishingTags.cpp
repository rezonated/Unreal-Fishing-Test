// Vanan Andreas - 2024


#include "FishingTags.h"

#include "GameplayTagsManager.h"

void FFishingTags::Startup(UGameplayTagsManager& GameplayTagsManager)
{
	FFishingTags& FishingTags = Get();
	
	FishingTags.Messaging_Fishing_Cast_Started = GameplayTagsManager.AddNativeGameplayTag( TEXT("Messaging.Fishing.Cast.Started"));
	FishingTags.Messaging_Fishing_Cast_Held = GameplayTagsManager.AddNativeGameplayTag(TEXT("Messaging.Fishing.Cast.Held"));
	FishingTags.Messaging_Fishing_Cast_Finished = GameplayTagsManager.AddNativeGameplayTag(TEXT("Messaging.Fishing.Cast.Finished"));
}
