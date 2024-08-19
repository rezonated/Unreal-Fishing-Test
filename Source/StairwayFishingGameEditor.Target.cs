// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StairwayFishingGameEditorTarget : TargetRules
{
	public StairwayFishingGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		ExtraModuleNames.AddRange(new[]
		{
			"StairwayFishingGameCore",
			"VAAnyUnreal",
			"VAAnyUnrealEditor",
			"VAAnyUnrealTests",
			"VAAnyUnrealUncookedOnly",
			"VAGameplayMessaging"
		});
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(new[]
		{
			"FishingFeature", "FishingGameplayTags", "FishingGameTypes", "StairwayFishingGameUI", "FishingFeatureEditor", "FishingFeatureTests"
		});
	}
}