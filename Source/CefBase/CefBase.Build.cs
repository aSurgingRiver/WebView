// Copyright aXiuShen. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
//using System.IO.Compression;
public class CefBase : ModuleRules
{
	public CefBase(ReadOnlyTargetRules Target) : base(Target)
	{

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        if (Target.Version.MajorVersion < 5) CppStandard = CppStandardVersion.Cpp17;
        string CEFRoot = Path.Combine(ModuleDirectory, "Public");
        PublicSystemIncludePaths.Add(Path.Combine(CEFRoot));
        //ZipFile.ExtractToDirectory("aa.zip", CEFRoot);
        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"cefForUe"
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
                "BaseBrowser",
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
