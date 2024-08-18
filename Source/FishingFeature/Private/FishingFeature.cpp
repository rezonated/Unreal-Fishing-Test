#include "FishingFeature/Public/FishingFeature.h"

#define LOCTEXT_NAMESPACE "FFishingFeatureModule"

void FFishingFeatureModule::StartupModule() {}

void FFishingFeatureModule::ShutdownModule() {}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFishingFeatureModule, FishingFeature)

DEFINE_LOG_CATEGORY(LogFishingFeature);