#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FFishingFeatureUIModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

DECLARE_LOG_CATEGORY_EXTERN(LogFishingFeatureUI, Log, All);