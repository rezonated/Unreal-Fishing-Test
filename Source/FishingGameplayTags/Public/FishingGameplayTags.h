#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Modules/ModuleManager.h"

class FFishingGameplayTagsModule final : public IModuleInterface
{
public:
	/*
	 * Called when the module is loaded, used to inject the fishing native gameplay tags into the gameplay tags manager via OnLastChanceToAddNativeTags event and then register the fishing native tags to the gameplay tags manager.
	 */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override {}

	void RegisterNativeTags();
};