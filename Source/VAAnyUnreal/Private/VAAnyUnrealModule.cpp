// Copyright - Vanan A. - 2024
#include "VAAnyUnreal.h"

#include "Modules/ModuleManager.h"
#include "IVAAnyUnrealModule.h"

#define LOCTEXT_NAMESPACE "FVAAnyUnrealModule"


class FVAAnyUnrealModule final : public IVAAnyUnrealModule
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override {}

	virtual void ShutdownModule() override {}
};


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVAAnyUnrealModule, VAAnyUnreal)