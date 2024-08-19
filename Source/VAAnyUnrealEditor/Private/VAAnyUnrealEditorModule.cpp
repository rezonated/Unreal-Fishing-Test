// Copyright - Vanan A. - 2024
#include "Editor/DetailCustomizations/VAAnyUnrealEditor_Customization.h"
#include "VAAnyUnrealEditor/Public/IVAAnyUnrealEditorModule.h"


#define LOCTEXT_NAMESPACE "FVAAnyUnrealEditorModule"

class FVAAnyUnrealEditorModule final : public IVAAnyUnrealEditorModule
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{
		FVAAnyUnrealEditor_Customization::Register();
	}

	virtual void ShutdownModule() override
	{
		FVAAnyUnrealEditor_Customization::Unregister();
	}
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVAAnyUnrealEditorModule, VAAnyUnrealEditor)