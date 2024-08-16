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

	FGameplayTag Messaging_Fishing_AnimInstance_StateChange;

	FGameplayTag AnimInstance_Fishing_State_Idling;
	FGameplayTag AnimInstance_Fishing_State_Throwing;
	FGameplayTag AnimInstance_Fishing_State_Reeling;
};
