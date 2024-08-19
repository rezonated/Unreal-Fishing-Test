#include "FishingFeatureEditor.h"

#include "DetailCustomization/DetailCustomization_FishingComponent.h"

#define LOCTEXT_NAMESPACE "FFishingFeatureEditorModule"

void FFishingFeatureEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout("DataAsset_FishingComponentConfig", FOnGetDetailCustomizationInstance::CreateStatic(&FDetailCustomization_FishingComponent::MakeInstance));
}

void FFishingFeatureEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout("DataAsset_FishingComponentConfig");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFishingFeatureEditorModule, FishingFeatureEditor)