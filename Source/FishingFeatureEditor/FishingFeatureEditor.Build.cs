using UnrealBuildTool;

public class FishingFeatureEditor : ModuleRules
{
	public FishingFeatureEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"InputCore"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore", "UMGEditor"
			}
		);

		OptimizeCode = CodeOptimization.InShippingBuildsOnly;
	}
}