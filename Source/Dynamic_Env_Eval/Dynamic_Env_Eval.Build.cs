// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Dynamic_Env_Eval : ModuleRules
{
	public Dynamic_Env_Eval(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Dynamic_Env_Eval",
			"Dynamic_Env_Eval/Variant_Platforming",
			"Dynamic_Env_Eval/Variant_Platforming/Animation",
			"Dynamic_Env_Eval/Variant_Combat",
			"Dynamic_Env_Eval/Variant_Combat/AI",
			"Dynamic_Env_Eval/Variant_Combat/Animation",
			"Dynamic_Env_Eval/Variant_Combat/Gameplay",
			"Dynamic_Env_Eval/Variant_Combat/Interfaces",
			"Dynamic_Env_Eval/Variant_Combat/UI",
			"Dynamic_Env_Eval/Variant_SideScrolling",
			"Dynamic_Env_Eval/Variant_SideScrolling/AI",
			"Dynamic_Env_Eval/Variant_SideScrolling/Gameplay",
			"Dynamic_Env_Eval/Variant_SideScrolling/Interfaces",
			"Dynamic_Env_Eval/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
