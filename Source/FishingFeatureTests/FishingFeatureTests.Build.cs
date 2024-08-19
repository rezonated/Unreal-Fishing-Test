using UnrealBuildTool;

public class FishingFeatureTests : ModuleRules
{
    public FishingFeatureTests(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "FishingGameTypes",
                "FunctionalTesting"
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

        OptimizeCode = CodeOptimization.Never;
    }
}