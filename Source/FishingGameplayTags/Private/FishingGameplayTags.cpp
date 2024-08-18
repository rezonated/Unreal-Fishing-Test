#include "FishingGameplayTags.h"

#include "FishingTags.h"

#define LOCTEXT_NAMESPACE "FFishingGameplayTagsModule"
#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFishingGameplayTagsModule, FishingGameplayTags)

void FFishingGameplayTagsModule::StartupModule()
{
	UGameplayTagsManager::Get().OnLastChanceToAddNativeTags().AddRaw(this, &FFishingGameplayTagsModule::RegisterNativeTags);
}

void FFishingGameplayTagsModule::RegisterNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	FFishingTags::Startup(GameplayTagsManager);

	GameplayTagsManager.OnLastChanceToAddNativeTags().RemoveAll(this);
}