using UnrealBuildTool;

public class StairwayFishingGameUI : ModuleRules
{
	public StairwayFishingGameUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UMG",
				"VAAnyUnreal",
				"VAGameplayMessaging",
				"GameplayTags",
				"FishingGameplayTags"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore", "FishingGameTypes"
			}
		);

		OptimizeCode = CodeOptimization.InShippingBuildsOnly;
	}
}