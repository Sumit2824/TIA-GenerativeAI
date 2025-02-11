// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TIA : ModuleRules
{
	public TIA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput",
             "HTTP", // Required for FHttpModule and HTTP requests
            "Json", // Required for JSON object creation and handling
            "JsonUtilities" // Required for JSON serialization/deserialization
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
           
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
