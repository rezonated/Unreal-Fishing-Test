// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FVAAnyUnrealTestsModule final : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};