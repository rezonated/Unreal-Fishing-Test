#include "FishingFeatureUI.h"

#define LOCTEXT_NAMESPACE "FFishingFeatureUIModule"

void FFishingFeatureUIModule::StartupModule() {}

void FFishingFeatureUIModule::ShutdownModule() {}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFishingFeatureUIModule, StairwayFishingGameUI)

DEFINE_LOG_CATEGORY(LogFishingFeatureUI);