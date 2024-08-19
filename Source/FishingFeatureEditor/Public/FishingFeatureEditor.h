#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FFishingFeatureEditorModule : public IModuleInterface
{
public:
	/*
	 * Called when the module is loaded, used to register the custom class layout for the fishing component data asset.
	 */
	virtual void StartupModule() override;

	/*
	 * Called when the module is unloaded, used to cleanup the custom class layout for the fishing component data asset.
	 */
	virtual void ShutdownModule() override;
};