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

	FGameplayTag Messaging_Fishing_Cast_Started;
	FGameplayTag Messaging_Fishing_Cast_Held;
	FGameplayTag Messaging_Fishing_Cast_Finished;
};
