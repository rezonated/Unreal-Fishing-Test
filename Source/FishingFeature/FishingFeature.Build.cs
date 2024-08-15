using UnrealBuildTool;

public class FishingFeature : ModuleRules
{
    public FishingFeature(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "VAGameplayMessaging",
                "FishingGameTypes",
                "VAAnyUnreal"
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