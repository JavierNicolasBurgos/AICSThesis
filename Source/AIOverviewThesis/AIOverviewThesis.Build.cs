// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AIOverviewThesis : ModuleRules
{
	public AIOverviewThesis(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		
		PrivateDependencyModuleNames.AddRange(new []{ "AIModule", "GameplayTasks", "NavigationSystem", "GameplayStateTreeModule", "GameplayTags" });
	}
}
