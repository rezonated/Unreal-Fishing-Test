using UnrealBuildTool;

public class VAAnyUnrealUncookedOnly : ModuleRules
{
	public VAAnyUnrealUncookedOnly(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UnrealEd",
				"BlueprintGraph",
				"KismetCompiler",
				"VAAnyUnreal"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore"
			}
		);
	}
}