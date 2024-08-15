// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StairwayFishingGameTarget : TargetRules
{
	public StairwayFishingGameTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		ExtraModuleNames.AddRange( new[]
		{
			"StairwayFishingGameCore",
			"VAAnyUnreal",
			"VALogging",
			"VAGameplayMessaging"
		} );
	}
}
