// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IVAAnyUnrealUncookedOnlyModule : public IModuleInterface
{
public:
	static IVAAnyUnrealUncookedOnlyModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IVAAnyUnrealUncookedOnlyModule>("VAAnyUnrealUncookedOnly");
	}
};