// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StairwayFishingGameCore : ModuleRules
{
	public StairwayFishingGameCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Slate",
			"UMG",
			"VAGameplayMessaging",
			"FishingGameplayTags",
			"GameplayTags",
			"VAAnyUnreal",
			"FishingGameTypes",
			"FishingFeature"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		OptimizeCode = CodeOptimization.InShippingBuildsOnly;
	}
}