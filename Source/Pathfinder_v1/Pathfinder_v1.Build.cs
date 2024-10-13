// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Pathfinder_v1 : ModuleRules
{
	public Pathfinder_v1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
