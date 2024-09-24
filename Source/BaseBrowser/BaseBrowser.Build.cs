// Copyright aXiuShen. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class BaseBrowser : ModuleRules
{
	public BaseBrowser(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        if (Target.Version.MajorVersion < 5) CppStandard = CppStandardVersion.Cpp17;
        string CEFRoot = Path.Combine(ModuleDirectory, "Public");
        PublicSystemIncludePaths.Add(Path.Combine(CEFRoot));
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);


        Int32 ue_version = Target.Version.MajorVersion * 10000 + Target.Version.MinorVersion * 100 + Target.Version.PatchVersion;
        PublicDefinitions.Add("WEBVIEW_ENGINE_VERSION=" + ue_version); //
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
                "MediaUtils",
                "MatureJson",
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
        PublicIncludePathModuleNames.AddRange(
            new string[] {
                "MediaUtils",
            }
        );

    }
}
