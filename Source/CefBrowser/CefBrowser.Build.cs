// Copyright aSurgingRiver, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Text;
//using System.Collections.Generic;
//using System.IO.Compression;

// Tools.DotNETCommon ;
// EpicGames.Core ;
using EpicGames.Core;

public class CefBrowser : ModuleRules
{
	public CefBrowser(ReadOnlyTargetRules Target) : base(Target)
	{
        //OptimizeCode = CodeOptimization.Never;
        //Type = ModuleType.CPlusPlus;
        if (Target.Version.MajorVersion<5)CppStandard = CppStandardVersion.Cpp17;
        //bPrecompile = false;
		bEnableExceptions = true;
		bUsePrecompiled = !bPrecompile;
		if (bUsePrecompiled) {
			PrecompileForTargets = PrecompileTargetsType.None;
		}
		else {
			if (isDependPlugin("OpenCV")) {// use for test
				PrivateDependencyModuleNames.AddRange(
					new string[] {
						"OpenCV",
						"OpenCVHelper"
					}
				);
			}
		}
		//PublicDefinitions.Add("WRAPPING_CEF_SHARED=1"); //
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        string privatep = Path.Combine(ModuleDirectory, "Private");
		if (Directory.Exists(privatep))
		{
            PrivateIncludePaths.Add(privatep);
            PrivateIncludePaths.Add(Path.Combine(privatep, "WidgetWrap"));
		}
		if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			PrivateDependencyModuleNames.Add("SDL2");
		}
        PublicSystemIncludePaths.Add(Path.Combine("Runtime"));
        PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Slate",
				"SlateCore",
				"Core",
				"CoreUObject",
				"ApplicationCore",
				"RHI",
                //"Launch",
                "RenderCore",
				"InputCore",
				"Serialization",
				"MediaUtils",
				"CefBase",
				"cefForUe",
				"OpenSSL",
				"ImageWrapper"
			}
		);
        if (Target.Type != TargetType.Server && Target.Platform == UnrealTargetPlatform.Win64)
		{
			AddEngineThirdPartyPrivateStaticDependencies(Target, "DX12");
			PrivateIncludePathModuleNames.AddRange(new string[]
			{
				"SlateRHIRenderer",
			});

			DynamicallyLoadedModuleNames.AddRange(new string[]
			{
				"SlateRHIRenderer",
			});
			PublicSystemLibraries.AddRange(new string[]
			{
				"comsuppw.lib",
				"dxgi.lib",
				"d3d11.lib",
				"d3d12.lib"
			});
			PublicDependencyModuleNames.AddRange(
				new string[]
                {
                "DX11",
                "DX12",
				"D3D11RHI",
				"D3D12RHI"
				}
			);

		}

		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
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

	}


	void CopyCefBrowser(string pluginPath, string projectFile, string sw)
	{
		string projName = Path.GetFileName(projectFile).Replace(".uproject", "");// 
		string projPath = Path.GetDirectoryName(projectFile); // 
		string srcMatch = Path.Combine(sw, "Development", "CefBrowser");
		string dstMatch = Path.Combine(projName, "Development", "CefBrowser");
		string pluginInter = Path.Combine(pluginPath, "Intermediate");
		if (!Directory.Exists(pluginInter)) return;
		foreach (string pathName in Directory.EnumerateDirectories(pluginInter, "CefBrowser", SearchOption.AllDirectories))
		{
			if (!pathName.EndsWith(srcMatch)) continue;
			foreach (string FileName in Directory.EnumerateFiles(pathName, "*.*", SearchOption.AllDirectories))
			{
				string name = Path.GetFileName(FileName);// 
				string srcBrowserPath = Path.GetDirectoryName(FileName);// 
				string dstBrowserPath = srcBrowserPath.Replace(pluginPath, projPath).Replace(srcMatch, dstMatch);
				string dstFile = Path.Combine(dstBrowserPath, name);
				//Console.WriteLine("dstBrowserPath=" + dstBrowserPath);
				if (!Directory.Exists(dstBrowserPath))
				{
					Directory.CreateDirectory(dstBrowserPath);
				}
				if (File.Exists(dstFile)) continue;
				System.IO.File.Copy(FileName, dstFile, true);
			}

		}
	}


	void CopyDir(string subfix, string outPath, string DstRoot)
	{
		//Console.WriteLine("===============================");
		//Console.WriteLine("outPath=" + outPath);
		//Console.WriteLine("DstRoot=" + DstRoot);
		if (!Directory.Exists(outPath)) return;
		foreach (string FileName in Directory.EnumerateFiles(outPath, "*" + subfix, SearchOption.AllDirectories))
		{
			string newFile = FileName.Replace(outPath, DstRoot);
			string file = Path.GetFileName(newFile).Replace(subfix, "");
			string pathDst = Path.GetDirectoryName(newFile);
			newFile = Path.Combine(pathDst, file);
			//Console.WriteLine("newFile=" + newFile);
			if (File.Exists(newFile)) continue;
			//Console.WriteLine("newFile=" + newFile + "  copy");
			if (!Directory.Exists(pathDst))
			{
				Directory.CreateDirectory(pathDst);
			}
			System.IO.File.Copy(FileName, newFile, true);
		}
	}

	void CheckLicense(string ProjectDir)
	{
		string licensePath = Path.Combine(ProjectDir, "Content", "license");
		if (!Directory.Exists(licensePath))
		{
			Directory.CreateDirectory(licensePath);
		}
		//if (!File.Exists(Path.Combine(licensePath, "webview.dat")))
		//	return;
		string GamePath = Path.Combine(ProjectDir, "Config");
		string GameCfg = Path.Combine(GamePath, "DefaultGame.ini");
		if (!Directory.Exists(GamePath)) {
			Directory.CreateDirectory(GamePath);
		}
		if (!File.Exists(GameCfg)){
			File.Create(GameCfg);
		}
		//if( File.OpenWrite(GameCfg)) return ;
		string content;
		try { content = File.ReadAllText(GameCfg/*, Encoding.UTF8*/); }
		catch
		{//
			return;
		}
		string licensePak = "+DirectoriesToAlwaysStageAsUFS=(Path=\"license\")";
		string licenseNode = "[/Script/UnrealEd.ProjectPackagingSettings]";
		if (content.Contains(licenseNode))
		{
			if (content.Contains(licensePak))
			{
				Console.WriteLine(GameCfg + " has configure!");
				return;//
			}
			content = content.Replace(licenseNode, licenseNode + "\n" + licensePak);
		}
		else
		{
			content += "\n\n" + licenseNode + "\n" + licensePak;
		}
		File.WriteAllText(GameCfg, content, Encoding.UTF8);
		Console.WriteLine(GameCfg + " auto configure!");
	}
	bool isDependPlugin(string plugin)
	{
		bool hasDep = false;
		FileReference pluginFile = new FileReference(Path.Combine(PluginDirectory, "WebView.uplugin"));
		PluginInfo Plugin = new PluginInfo(pluginFile, PluginType.Project);
		foreach (PluginReferenceDescriptor desc in Plugin.Descriptor.Plugins)
		{
			if (desc.Name != plugin) continue;
			hasDep = desc.bEnabled;
			break;
		}
		return hasDep;
	}

}
