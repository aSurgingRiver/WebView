// Copyright aXiuShen. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class MatureJson : ModuleRules
{
	public MatureJson(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);

			int EngineVersion = Target.Version.MajorVersion * 100 + Target.Version.MinorVersion;
			PublicDefinitions.Add("MATUREJSON_VERSION=" + EngineVersion.ToString());
		if(EngineVersion<=426) CppStandard = CppStandardVersion.Cpp17;
		else if(EngineVersion <= 501) CppStandard = CppStandardVersion.Cpp17;
		else CppStandard = CppStandardVersion.Default;

        PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
            {
                "Slate",
                "SlateCore",
                "Core",
                "CoreUObject",
                "ApplicationCore",
                "RHI",
                "RenderCore",
                "InputCore",
                "Serialization",
                "RapidForUe"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
                "Slate",
				"SlateCore",
				"Projects",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
