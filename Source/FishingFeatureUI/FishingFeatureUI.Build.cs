using UnrealBuildTool;

public class FishingFeatureUI : ModuleRules
{
    public FishingFeatureUI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

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
                "SlateCore"
            }
        );

        OptimizeCode = CodeOptimization.InShippingBuildsOnly;
    }
}