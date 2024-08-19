using UnrealBuildTool;

public class FishingFeature : ModuleRules
{
	public FishingFeature(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"VAGameplayMessaging",
				"FishingGameTypes",
				"VAAnyUnreal",
				"GameplayTags",
				"StairwayFishingGameUI",
				"UMG",
				"Slate"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore", "FishingGameplayTags"
			}
		);

		OptimizeCode = CodeOptimization.InShippingBuildsOnly;
	}
}