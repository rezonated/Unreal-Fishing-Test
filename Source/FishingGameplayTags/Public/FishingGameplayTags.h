#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Modules/ModuleManager.h"

class FFishingGameplayTagsModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override {}

	void RegisterNativeTags();
};