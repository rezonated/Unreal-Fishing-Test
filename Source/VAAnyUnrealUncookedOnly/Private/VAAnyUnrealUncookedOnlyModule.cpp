// Copyright - Vanan A. - 2024
#include "VAAnyUnrealUncookedOnly.h"


#include "IVAAnyUnrealUncookedOnlyModule.h"


#define LOCTEXT_NAMESPACE "FVAAnyUnrealUncookedOnlyModule"

class FVAAnyUnrealUncookedOnlyModule final : public IVAAnyUnrealUncookedOnlyModule
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override {}

	virtual void ShutdownModule() override {}
};


#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVAAnyUnrealUncookedOnlyModule, VAAnyUnrealUncookedOnly)