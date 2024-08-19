// Copyright - Vanan A. - 2024
#pragma once

#include "VAAnyUnreal.h"

#include "Modules/ModuleManager.h"


class VAANYUNREAL_API IVAAnyUnrealModule : public IModuleInterface
{
public:
	static IVAAnyUnrealModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IVAAnyUnrealModule>("VAAnyUnreal");
	}
};