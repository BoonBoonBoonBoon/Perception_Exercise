// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Perception : ModuleRules
{
	public Perception(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
		
        
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
			"EnhancedInput", "AIModule",
			"GameplayTasks", "NavigationSystem" });
	}
}
