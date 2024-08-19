// Copyright - Vanan A. - 2024
#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleManager.h"

class IVAAnyUnrealEditorModule : public IModuleInterface
{
public:
	static IVAAnyUnrealEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IVAAnyUnrealEditorModule>("VAAnyUnrealEditor");
	}
};