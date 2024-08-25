// Copyright aXiuShen. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Text;
using System.Collections.Generic;


public class cefForUe : ModuleRules
{
    public cefForUe(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        //PrintConfig("cefForUe");
		//Console.WriteLine(Target.bBuildEditor ? "editor":"runtime");
        //string versionCEF="cef_95.4638";
        //string versionCEF = "cef_103.5060";
        //string versionCEF="cef_88.4324";
        if (Target.Platform == UnrealTargetPlatform.Win64) {
            //InitCEF3_Win("cef_103.5060");
            InitCEF3_Win("cef_120.6099");
            //InitCEF3_Win("cef_115.5790");
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            InitCEF3_Linux("cef_103.5060");
        }
        //else if (Target.Platform == UnrealTargetPlatform.Mac)
        //{
        //    InitCEF3_Mac("cef_103.5060","mac");
        //}
        else {
            return;
        }
    }
    void MergeFile(string PathRoot)
    {
        string split = ".split";
        // merge file
        Dictionary<string, Dictionary<int, string>> mapFile = new Dictionary<string, Dictionary<int, string>>();
        foreach (string FileName in Directory.EnumerateFiles(PathRoot, "*" + split, SearchOption.AllDirectories))
        {
            string file = Path.GetFileName(FileName);
            string filePath = Path.GetDirectoryName(FileName);
            if (!filePath.EndsWith(".dir")) continue;
            string splitName = Path.GetFileName(filePath).Replace(".dir", "");
            string splitPath = Path.GetDirectoryName(filePath);
            string splitPN = Path.Combine(splitPath, splitName);
            if (File.Exists(splitPN)) continue;
            if (!mapFile.ContainsKey(splitPN))
                mapFile.Add(splitPN, new Dictionary<int, string>());
            int idx = int.Parse(file.Replace(split, ""));
            mapFile[splitPN].Add(idx, FileName);
        }
        const int maxBuff = 1024 * 1024 * 100;
        byte[] readBuff = new byte[maxBuff];//
        foreach (KeyValuePair<string, Dictionary<int, string>> kvp in mapFile)
        {
            if (kvp.Value.Count == 0) continue;
            FileStream fileDst = new FileStream(kvp.Key, FileMode.OpenOrCreate);
            for(int index=1;index<=kvp.Value.Count;index++)
            {
                string filePathSplit = kvp.Value[index];
                FileStream fileSrc = new FileStream(filePathSplit, FileMode.Open);
                long fileSize = fileSrc.Length;
                while (0 < fileSize)
                {
                    int readLen = fileSrc.Read(readBuff, 0, maxBuff);
                    fileDst.Write(readBuff, 0, readLen);
                    fileSize -= readLen;
                }
            }
        }
    }

    void InitCEF3_PUB(string CEFRoot,string CEFVersion,string renderName, List<string> Dlls)
    {
        //string CEFRoot = Path.Combine(ModuleDirectory, CEFVersion, platform);
        string LibraryPath = Path.Combine(CEFRoot,"lib");
        MergeFile(CEFRoot);
        string[] branchs = CEFVersion.Split('.'); 
        string branch ="";
        if (2 <= branchs.Length) branch = branchs[1];
        Int32 ue_version = Target.Version.MajorVersion*10000+Target.Version.MinorVersion*100+Target.Version.PatchVersion;
        PublicSystemIncludePaths.Add(Path.Combine(CEFRoot));
        PublicDefinitions.Add("CEF3_RENDER=\"" + renderName + "\""); //
        PublicDefinitions.Add("CEF3_VERSION=\"" + CEFVersion + "\""); //
        PublicDefinitions.Add("CEF3_BRANCH=" + branch + ""); //
        PublicDefinitions.Add("CEF3_UE_ENGINE_VERSION=" + ue_version ); //
        //List<string> Dlls = new List<string>();
        Dlls.Add("icudtl.dat");
        Dlls.Add("snapshot_blob.bin");
        Dlls.Add("v8_context_snapshot.bin");
        Dlls.Add("vk_swiftshader_icd.json");
        Dlls.Add("LICENSE.txt");
        foreach (string Dll in Dlls)
        {
            string file = Path.Combine(LibraryPath, Dll);
            if (!File.Exists(file)) continue;
            RuntimeDependencies.Add(file);
        }
        foreach (string FileName in Directory.EnumerateFiles(LibraryPath, "*.pak", SearchOption.AllDirectories))
        {
            RuntimeDependencies.Add(FileName);
        }
        RuntimeDependencies.Add(Path.Combine(LibraryPath, renderName));
    }
    void InitCEF3_Win(string CEFVersion)
    {
        string CEFRoot = Path.Combine(ModuleDirectory, CEFVersion, "win64");
        string LibraryPath = Path.Combine(CEFRoot, "lib");
        List<string> Dlls = new List<string>();
        Dlls.Add("killnoparent.exe");
        InitCEF3_PUB(CEFRoot, CEFVersion, "cefhelper.exe", Dlls);

        PublicDefinitions.Add("USING_CEF_SHARED=1"); //
        PublicDefinitions.Add("CEF_WINDOWS=1"); //
        PublicDefinitions.Add("WEBVIEW_CUSTOMIZED_CORE"); //
        foreach (string FileName in Directory.EnumerateFiles(LibraryPath, "*.lib", SearchOption.TopDirectoryOnly)) {
            PublicAdditionalLibraries.Add(FileName);
        }
        foreach (string FileName in Directory.EnumerateFiles(LibraryPath, "*.dll", SearchOption.TopDirectoryOnly)) {
            PublicDelayLoadDLLs.Add(System.IO.Path.GetFileName(FileName));
            RuntimeDependencies.Add(FileName);
        }
        string swiftshader = Path.Combine(LibraryPath, "swiftshader");
        if(Directory.Exists(swiftshader))
        foreach (string FileName in Directory.EnumerateFiles(swiftshader, "*.dll", SearchOption.TopDirectoryOnly))
        {
            RuntimeDependencies.Add(FileName);
        }
    }
    void InitCEF3_Mac(string CEFVersion,string arch)
    {
        string CEFRoot = Path.Combine(ModuleDirectory, CEFVersion, arch);
        string LibraryPath = Path.Combine(CEFRoot, "lib");
        MergeFile(LibraryPath);
        PublicSystemIncludePaths.Add(Path.Combine(CEFRoot));
        PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "libcef_dll_wrapper.a"));

        string[] branchs = CEFVersion.Split('.');
        string branch = "";
        if (2 <= branchs.Length) branch = branchs[1];

        Int32 ue_version = Target.Version.MajorVersion * 10000 + Target.Version.MinorVersion * 100 + Target.Version.PatchVersion;
        PublicDefinitions.Add("CEF3_UE_ENGINE_VERSION=" + ue_version); //
        PublicDefinitions.Add("CEF3_RENDER=\"cefhelper\""); //
        PublicDefinitions.Add("CEF3_VERSION=\"" + CEFVersion + "\""); //
        PublicDefinitions.Add("CEF3_BRANCH=" + branch + ""); //
        PublicDefinitions.Add("PLATFORM_LINUXAARCH64=0"); //
        PublicDefinitions.Add("CEF_MAC=1"); //
        PublicDefinitions.Add("WEBVIEW_CUSTOMIZED_CORE"); //
        PrivateRuntimeLibraryPaths.Add(LibraryPath);
        foreach (string FileName in Directory.EnumerateFiles(LibraryPath, "*", SearchOption.AllDirectories))
        {
            if (FileName.EndsWith(".split")) continue;//
            // if (FileName.EndsWith(".dylib"))PublicAdditionalLibraries.Add(FileName);
            if (FileName.EndsWith(".lproj")) AdditionalBundleResources.Add(new BundleResource(FileName,bShouldLog: false));
            RuntimeDependencies.Add(FileName);
        }
    }
    void InitCEF3_Linux(string CEFVersion)
    {
        string LINUX_MULTIARCH_ROOT = Environment.GetEnvironmentVariable("LINUX_MULTIARCH_ROOT");
        string CEFRoot =Path.Combine(ModuleDirectory, CEFVersion,"linux");// LINUX_MULTIARCH_ROOT
        //PathList.FullPathName()
        string LibraryPath = Path.Combine(CEFRoot, "lib");
        List<string> Dlls = new List<string>();
        Dlls.Add("chrome-sandbox");
        Dlls.Add("libvulkan.so.1");
        Dlls.Add("libvulkan.so.1.cef");
        InitCEF3_PUB(CEFRoot, CEFVersion, "cefhelper", Dlls);
        //MergeFile(CEFRoot);
        string libcef_path = "" ;
        String ProjectBin = Path.Combine(Path.GetDirectoryName(Target.ProjectFile.ToString()), "Binaries", "Linux");
        if (LINUX_MULTIARCH_ROOT != "")
        {
            PublicDefinitions.Add("WV_CROSS_BUILE=1"); //
        }
        PublicDefinitions.Add("CEF_LINUX=1"); //
        PublicDefinitions.Add("WEBVIEW_CUSTOMIZED_CORE"); //
        PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "libcef_dll_wrapper.a"));
        PrivateRuntimeLibraryPaths.Add(LibraryPath);
        foreach (string FileName in Directory.EnumerateFiles(LibraryPath, "*.so", SearchOption.TopDirectoryOnly))
        {
            if(FileName.EndsWith("libcef.so"))
            { //
                libcef_path = System.IO.Path.GetDirectoryName(FileName);
                PublicAdditionalLibraries.Add(FileName);
            }
            RuntimeDependencies.Add(FileName);
        }
        //
        string swiftshader = Path.Combine(LibraryPath, "swiftshader");
        if (Directory.Exists(swiftshader))
        foreach (string FileName in Directory.EnumerateFiles(swiftshader, "*.so", SearchOption.TopDirectoryOnly))
        {
            RuntimeDependencies.Add(FileName);
        }
        MakeStartScript(libcef_path);
    }
    void MakeStartScript(string libcef_path)
    {
        string project_name = Target.ProjectFile.GetFileNameWithoutExtension();
        string project_path = Target.ProjectFile.ToString().Replace(Target.ProjectFile.GetFileName(), "");
        libcef_path = libcef_path.Replace(project_path, "");
        libcef_path = Path.Combine("`pwd`", project_name, libcef_path).Replace("\\","/");
        string Architecture = "Linux";
        if (Target.Architecture.ToString() == "Arm64"){
            Architecture = "LinuxAArch64";
        }
        string run_script = "";
        run_script += "#!/bin/sh \n";
        run_script += "# Please copy this file to the packaging directory ,And cover. \n";
        run_script += "CEF_PATH=" + libcef_path + " \n";
        run_script += "chmod 775 $CEF_PATH/* \n";
        run_script += "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CEF_PATH \n";
        run_script += "THISCPU=$(uname -m) \n";
        run_script += "rm -rf $CEF_PATH/libvulkan.so.1 \n";
        run_script += "ln -s /usr/lib/${THISCPU}-linux-gnu/libvulkan.so.1 $CEF_PATH/libvulkan.so.1 \n";

        run_script += "UE_TRUE_SCRIPT_NAME=$(echo \\\"$0\\\" | xargs readlink -f) \n";
        run_script += "UE_PROJECT_ROOT=$(dirname \"$UE_TRUE_SCRIPT_NAME\")\n";
        run_script += "chmod +x \"$UE_PROJECT_ROOT/" + project_name + "/Binaries/"+ Architecture + "/" + project_name + "\" \n";
        run_script += "\"$UE_PROJECT_ROOT/" + project_name + "/Binaries/"+ Architecture + "/" + project_name + "\" WebViewDemo \"$@\" \n";
        string run_path = Target.ProjectFile.Directory.ToString();
        string run_file = Path.Combine(run_path, project_name + ".sh");
        if (File.Exists(run_file)) File.Delete(run_file);
        File.WriteAllText(run_file, run_script, Encoding.UTF8);
        File.SetAttributes(run_file, File.GetAttributes(run_file) | FileAttributes.System);
    }
    //void PrintConfig(string Module)
    //{
    //    Console.WriteLine("===================" + Module + " Begin ===========================");
    //    Console.WriteLine("Name=" + Target.Name);
    //    //Console.WriteLine("File=" + Target.File);
    //    //Console.WriteLine("TargetSourceFile=" + Target.TargetSourceFile);
    //    Console.WriteLine("Platform=" + Target.Platform);
    //    Console.WriteLine("Configuration=" + Target.Configuration);
    //    Console.WriteLine("Architecture=" + Target.Architecture);
    //    Console.WriteLine("ProjectFile=" + Target.ProjectFile);
    //    Console.WriteLine("Version.MajorVersion=" + Target.Version.MajorVersion);
    //    Console.WriteLine("Version.MinorVersion=" + Target.Version.MinorVersion);
    //    Console.WriteLine("Version.PatchVersion=" + Target.Version.PatchVersion);
    //    Console.WriteLine("Type=" + Target.Type);
    //    Console.WriteLine("DefaultBuildSettings=" + Target.DefaultBuildSettings);
    //    //Console.WriteLine("ConfigValueTracker=" + Target.ConfigValueTracker);
    //    Console.WriteLine("bUsesSteam=" + Target.bUsesSteam);
    //    Console.WriteLine("bUsesCEF3=" + Target.bUsesCEF3);
    //    Console.WriteLine("bUsesSlate=" + Target.bUsesSlate);
    //    Console.WriteLine("bUseStaticCRT=" + Target.bUseStaticCRT);
    //    Console.WriteLine("bDebugBuildsActuallyUseDebugCRT=" + Target.bDebugBuildsActuallyUseDebugCRT);
    //    Console.WriteLine("bLegalToDistributeBinary=" + Target.bLegalToDistributeBinary);
    //    Console.WriteLine("UndecoratedConfiguration=" + Target.UndecoratedConfiguration);
    //    Console.WriteLine("bAllowHotReload=" + Target.bAllowHotReload);
    //    Console.WriteLine("bBuildAllModules=" + Target.bBuildAllModules);
    //    //Console.WriteLine("bRuntimeDependenciesComeFromBuildPlugins=" + Target.bRuntimeDependenciesComeFromBuildPlugins);
    //    Console.WriteLine("PakSigningKeysFile=" + Target.PakSigningKeysFile);
    //    Console.WriteLine("SolutionDirectory=" + Target.SolutionDirectory);
    //    //Console.WriteLine("CustomConfig=" + Target.CustomConfig);
    //    Console.WriteLine("bBuildInSolutionByDefault=" + Target.bBuildInSolutionByDefault);
    //    Console.WriteLine("ExeBinariesSubFolder=" + Target.ExeBinariesSubFolder);
    //    Console.WriteLine("GeneratedCodeVersion=" + Target.GeneratedCodeVersion);
    //    Console.WriteLine("bEnableMeshEditor=" + Target.bEnableMeshEditor);
    //    //Console.WriteLine("bUseVerse=" + Target.bUseVerse);
    //    //Console.WriteLine("bCompileChaos=" + Target.bCompileChaos);
    //    //Console.WriteLine("bUseChaos=" + Target.bUseChaos);
    //    Console.WriteLine("bUseChaosMemoryTracking=" + Target.bUseChaosMemoryTracking);
    //    Console.WriteLine("bUseChaosChecked=" + Target.bUseChaosChecked);
    //    //Console.WriteLine("bCustomSceneQueryStructure=" + Target.bCustomSceneQueryStructure);
    //    //Console.WriteLine("bCompilePhysX=" + Target.bCompilePhysX);
    //    //Console.WriteLine("bCompileAPEX=" + Target.bCompileAPEX);
    //    //Console.WriteLine("bCompileNvCloth=" + Target.bCompileNvCloth);
    //    Console.WriteLine("bCompileICU=" + Target.bCompileICU);
    //    Console.WriteLine("bCompileCEF3=" + Target.bCompileCEF3);
    //    Console.WriteLine("bCompileISPC=" + Target.bCompileISPC);
    //    //Console.WriteLine("bCompilePython=" + Target.bCompilePython);
    //    Console.WriteLine("bUseChaosChecked=" + Target.bUseChaosChecked);
    //    Console.WriteLine("bBuildEditor=" + Target.bBuildEditor);
    //    Console.WriteLine("bBuildRequiresCookedData=" + Target.bBuildRequiresCookedData);
    //    Console.WriteLine("bBuildWithEditorOnlyData=" + Target.bBuildWithEditorOnlyData);
    //    Console.WriteLine("bBuildDeveloperTools=" + Target.bBuildDeveloperTools);
    //    //Console.WriteLine("bBuildTargetDeveloperTools=" + Target.bBuildTargetDeveloperTools);
    //    Console.WriteLine("bForceBuildTargetPlatforms=" + Target.bForceBuildTargetPlatforms);
    //    Console.WriteLine("bForceBuildShaderFormats=" + Target.bForceBuildShaderFormats);
    //    Console.WriteLine("bCompileCustomSQLitePlatform=" + Target.bCompileCustomSQLitePlatform);
    //    Console.WriteLine("bUseCacheFreedOSAllocs=" + Target.bUseCacheFreedOSAllocs);
    //    Console.WriteLine("bCompileAgainstEngine=" + Target.bCompileAgainstEngine);
    //    Console.WriteLine("bCompileAgainstCoreUObject=" + Target.bCompileAgainstCoreUObject);
    //    Console.WriteLine("bCompileAgainstApplicationCore=" + Target.bCompileAgainstApplicationCore);
    //    Console.WriteLine("bCompileRecast=" + Target.bCompileRecast);
    //    Console.WriteLine("bCompileNavmeshSegmentLinks=" + Target.bCompileNavmeshSegmentLinks);
    //    Console.WriteLine("bCompileNavmeshClusterLinks=" + Target.bCompileNavmeshClusterLinks);
    //    Console.WriteLine("bCompileSpeedTree=" + Target.bCompileSpeedTree);
    //    Console.WriteLine("bForceEnableExceptions=" + Target.bForceEnableExceptions);
    //    Console.WriteLine("bForceEnableObjCExceptions=" + Target.bForceEnableObjCExceptions);
    //    Console.WriteLine("bForceEnableRTTI=" + Target.bForceEnableRTTI);
    //    Console.WriteLine("bUseInlining=" + Target.bUseInlining);
    //    Console.WriteLine("bWithServerCode=" + Target.bWithServerCode);
    //    Console.WriteLine("bWithPushModel=" + Target.bWithPushModel);
    //    Console.WriteLine("bCompileWithStatsWithoutEngine=" + Target.bCompileWithStatsWithoutEngine);
    //    Console.WriteLine("bCompileWithPluginSupport=" + Target.bCompileWithPluginSupport);
    //    Console.WriteLine("bIncludePluginsForTargetPlatforms=" + Target.bIncludePluginsForTargetPlatforms);
    //    Console.WriteLine("bCompileWithAccessibilitySupport=" + Target.bCompileWithAccessibilitySupport);
    //    Console.WriteLine("bWithPerfCounters=" + Target.bWithPerfCounters);
    //    Console.WriteLine("bWithLiveCoding=" + Target.bWithLiveCoding);
    //    Console.WriteLine("bUseDebugLiveCodingConsole=" + Target.bUseDebugLiveCodingConsole);
    //    Console.WriteLine("bWithDirectXMath=" + Target.bWithDirectXMath);
    //    Console.WriteLine("bUseLoggingInShipping=" + Target.bUseLoggingInShipping);
    //    Console.WriteLine("bLoggingToMemoryEnabled=" + Target.bLoggingToMemoryEnabled);
    //    Console.WriteLine("bUseLauncherChecks=" + Target.bUseLauncherChecks);
    //    Console.WriteLine("bUseChecksInShipping=" + Target.bUseChecksInShipping);
    //    Console.WriteLine("bUseEstimatedUtcNow=" + Target.bUseEstimatedUtcNow);
    //    Console.WriteLine("bCompileFreeType=" + Target.bCompileFreeType);
    //    //Console.WriteLine("bCompileForSize=" + Target.bCompileForSize);
    //    //Console.WriteLine("bRetainFramePointers=" + Target.bRetainFramePointers);
    //    Console.WriteLine("bForceCompileDevelopmentAutomationTests=" + Target.bForceCompileDevelopmentAutomationTests);
    //    Console.WriteLine("bForceCompilePerformanceAutomationTests=" + Target.bForceCompilePerformanceAutomationTests);
    //    //Console.WriteLine("bForceDisableAutomationTests=" + Target.bForceDisableAutomationTests);
    //    Console.WriteLine("bUseXGEController=" + Target.bUseXGEController);
    //    Console.WriteLine("bEventDrivenLoader=" + Target.bEventDrivenLoader);
    //    //Console.WriteLine("NativePointerMemberBehaviorOverride=" + Target.NativePointerMemberBehaviorOverride);
    //    Console.WriteLine("bIWYU=" + Target.bIWYU);
    //    Console.WriteLine("bEnforceIWYU=" + Target.bEnforceIWYU);
    //    Console.WriteLine("bHasExports=" + Target.bHasExports);
    //    Console.WriteLine("bPrecompile=" + Target.bPrecompile);
    //    Console.WriteLine("bEnableOSX109Support=" + Target.bEnableOSX109Support);
    //    Console.WriteLine("bIsBuildingConsoleApplication=" + Target.bIsBuildingConsoleApplication);
    //    Console.WriteLine("bBuildAdditionalConsoleApp=" + Target.bBuildAdditionalConsoleApp);
    //    Console.WriteLine("bDisableSymbolCache=" + Target.bDisableSymbolCache);
    //    Console.WriteLine("bUseUnityBuild=" + Target.bUseUnityBuild);
    //    Console.WriteLine("bAdaptiveUnityDisablesOptimizations=" + Target.bAdaptiveUnityDisablesOptimizations);
    //    Console.WriteLine("bAdaptiveUnityDisablesPCH=" + Target.bAdaptiveUnityDisablesPCH);
    //    Console.WriteLine("bAdaptiveUnityDisablesPCHForProject=" + Target.bAdaptiveUnityDisablesPCHForProject);
    //    Console.WriteLine("bAdaptiveUnityCreatesDedicatedPCH=" + Target.bAdaptiveUnityCreatesDedicatedPCH);
    //    Console.WriteLine("bAdaptiveUnityEnablesEditAndContinue=" + Target.bAdaptiveUnityEnablesEditAndContinue);
    //    //Console.WriteLine("bAdaptiveUnityCompilesHeaderFiles=" + Target.bAdaptiveUnityCompilesHeaderFiles);
    //    Console.WriteLine("MinGameModuleSourceFilesForUnityBuild=" + Target.MinGameModuleSourceFilesForUnityBuild);
    //    //Console.WriteLine("DefaultWarningLevel=" + Target.DefaultWarningLevel);
    //    //Console.WriteLine("DeprecationWarningLevel=" + Target.DeprecationWarningLevel);
    //    Console.WriteLine("ShadowVariableWarningLevel=" + Target.ShadowVariableWarningLevel);
    //    Console.WriteLine("UnsafeTypeCastWarningLevel=" + Target.UnsafeTypeCastWarningLevel);
    //    Console.WriteLine("bUndefinedIdentifierErrors=" + Target.bUndefinedIdentifierErrors);
    //    //Console.WriteLine("bWarningsAsErrors=" + Target.bWarningsAsErrors);
    //    Console.WriteLine("bUseFastMonoCalls=" + Target.bUseFastMonoCalls);
    //    Console.WriteLine("NumIncludedBytesPerUnityCPP=" + Target.NumIncludedBytesPerUnityCPP);
    //    Console.WriteLine("bStressTestUnity=" + Target.bStressTestUnity);
    //    Console.WriteLine("bDisableDebugInfo=" + Target.bDisableDebugInfo);
    //    Console.WriteLine("bDisableDebugInfoForGeneratedCode=" + Target.bDisableDebugInfoForGeneratedCode);
    //    Console.WriteLine("bOmitPCDebugInfoInDevelopment=" + Target.bOmitPCDebugInfoInDevelopment);
    //    Console.WriteLine("bUsePDBFiles=" + Target.bUsePDBFiles);
    //    Console.WriteLine("bUsePCHFiles=" + Target.bUsePCHFiles);
    //    Console.WriteLine("bPreprocessOnly=" + Target.bPreprocessOnly);
    //    Console.WriteLine("MinFilesUsingPrecompiledHeader=" + Target.MinFilesUsingPrecompiledHeader);
    //    Console.WriteLine("bForcePrecompiledHeaderForGameModules=" + Target.bForcePrecompiledHeaderForGameModules);
    //    Console.WriteLine("bUseIncrementalLinking=" + Target.bUseIncrementalLinking);
    //    Console.WriteLine("bAllowLTCG=" + Target.bAllowLTCG);
    //    //Console.WriteLine("bPreferThinLTO=" + Target.bPreferThinLTO);
    //    Console.WriteLine("bPGOProfile=" + Target.bPGOProfile);
    //    Console.WriteLine("bPGOOptimize=" + Target.bPGOOptimize);
    //    Console.WriteLine("bSupportEditAndContinue=" + Target.bSupportEditAndContinue);
    //    Console.WriteLine("bOmitFramePointers=" + Target.bOmitFramePointers);
    //    //Console.WriteLine("bEnableCppModules=" + Target.bEnableCppModules);
    //    //Console.WriteLine("bEnableCppCoroutinesForEvaluation=" + Target.bEnableCppCoroutinesForEvaluation);
    //    //Console.WriteLine("bUseMallocProfiler=" + Target.bUseMallocProfiler);
    //    Console.WriteLine("bUseSharedPCHs=" + Target.bUseSharedPCHs);
    //    Console.WriteLine("bUseShippingPhysXLibraries=" + Target.bUseShippingPhysXLibraries);
    //    Console.WriteLine("bCheckLicenseViolations=" + Target.bCheckLicenseViolations);
    //    Console.WriteLine("bBreakBuildOnLicenseViolation=" + Target.bBreakBuildOnLicenseViolation);
    //    Console.WriteLine("bUseFastPDBLinking=" + Target.bUseFastPDBLinking);
    //    Console.WriteLine("bCreateMapFile=" + Target.bCreateMapFile);
    //    Console.WriteLine("bAllowRuntimeSymbolFiles=" + Target.bAllowRuntimeSymbolFiles);
    //    Console.WriteLine("BundleVersion=" + Target.BundleVersion);
    //    Console.WriteLine("bDeployAfterCompile=" + Target.bDeployAfterCompile);
    //    Console.WriteLine("bAllowRemotelyCompiledPCHs=" + Target.bAllowRemotelyCompiledPCHs);
    //    Console.WriteLine("bCheckSystemHeadersForModification=" + Target.bCheckSystemHeadersForModification);
    //    Console.WriteLine("bDisableLinking=" + Target.bDisableLinking);
    //    Console.WriteLine("bFormalBuild=" + Target.bFormalBuild);
    //    Console.WriteLine("bUseAdaptiveUnityBuild=" + Target.bUseAdaptiveUnityBuild);
    //    Console.WriteLine("bFlushBuildDirOnRemoteMac=" + Target.bFlushBuildDirOnRemoteMac);
    //    Console.WriteLine("bPrintToolChainTimingInfo=" + Target.bPrintToolChainTimingInfo);
    //    Console.WriteLine("bParseTimingInfoForTracing=" + Target.bParseTimingInfoForTracing);
    //    Console.WriteLine("bPublicSymbolsByDefault=" + Target.bPublicSymbolsByDefault);
    //    Console.WriteLine("ToolChainName=" + Target.ToolChainName);
    //    Console.WriteLine("bLegacyPublicIncludePaths=" + Target.bLegacyPublicIncludePaths);
    //    Console.WriteLine("CppStandard=" + Target.CppStandard);
    //    //Console.WriteLine("bNoManifestChanges=" + Target.bNoManifestChanges);
    //    Console.WriteLine("BuildVersion=" + Target.BuildVersion);
    //    Console.WriteLine("LinkType=" + Target.LinkType);
    //    Console.WriteLine("LaunchModuleName=" + Target.LaunchModuleName);
    //    Console.WriteLine("ExportPublicHeader=" + Target.ExportPublicHeader);
    //    Console.WriteLine("BuildEnvironment=" + Target.BuildEnvironment);
    //    Console.WriteLine("bOverrideBuildEnvironment=" + Target.bOverrideBuildEnvironment);
    //    Console.WriteLine("AdditionalCompilerArguments=" + Target.AdditionalCompilerArguments);
    //    Console.WriteLine("AdditionalLinkerArguments=" + Target.AdditionalLinkerArguments);
    //    //Console.WriteLine("MemoryPerActionGB=" + Target.MemoryPerActionGB);
    //    Console.WriteLine("GeneratedProjectName=" + Target.GeneratedProjectName);
    //    Console.WriteLine("AndroidPlatform=" + Target.AndroidPlatform);
    //    Console.WriteLine("LinuxPlatform=" + Target.LinuxPlatform);
    //    Console.WriteLine("IOSPlatform=" + Target.IOSPlatform);
    //    Console.WriteLine("MacPlatform=" + Target.MacPlatform);
    //    Console.WriteLine("WindowsPlatform=" + Target.WindowsPlatform);
    //    //Console.WriteLine("HoloLensPlatform=" + Target.HoloLensPlatform);
    //    Console.WriteLine("bShouldCompileAsDLL=" + Target.bShouldCompileAsDLL);
    //    Console.WriteLine("bGenerateProjectFiles=" + Target.bGenerateProjectFiles);
    //    Console.WriteLine("bIsEngineInstalled=" + Target.bIsEngineInstalled);
    //    Console.WriteLine("RelativeEnginePath=" + Target.RelativeEnginePath);
    //    Console.WriteLine("UEThirdPartySourceDirectory=" + Target.UEThirdPartySourceDirectory);
    //    Console.WriteLine("UEThirdPartyBinariesDirectory=" + Target.UEThirdPartyBinariesDirectory);
    //    //Console.WriteLine("IsInPlatformGroup=" + Target.IsInPlatformGroup);
    //    //Console.WriteLine("IsPlatformOptedIn=" + Target.IsPlatformOptedIn);
    //    Console.WriteLine("===================" + Module + " End ===========================");
    //}
}
