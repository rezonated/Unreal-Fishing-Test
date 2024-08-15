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
                "UMG",
                "FishingGameplayTags",
                "GameplayTags",
                "VAAnyUnreal"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
    }
}