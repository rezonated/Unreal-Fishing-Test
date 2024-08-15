using UnrealBuildTool;

public class VAAnyUnrealEditor : ModuleRules
{
    public VAAnyUnrealEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "VAAnyUnreal",
                "InputCore",
                "PropertyEditor",
                "StructViewer",
                "EditorStyle",
                "UnrealEd",
                "BlueprintGraph"
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