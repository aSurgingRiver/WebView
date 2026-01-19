// Copyright aXiuShen. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.IO.Compression;
using System.Text;

// Tools.DotNETCommon ;
// EpicGames.Core ;
using EpicGames.Core;

namespace UnrealBuildTool.Rules
{
    public class WebView : ModuleRules
    {
        public struct PluginLoad {
            public PluginLoad(bool _Bridge, bool _WebBrowser, bool _WebView)
            {
                Bridge = _Bridge;
                WebBrowser = _WebBrowser;
                WebView = _WebView;
            }
            public bool Bridge ;
            public bool WebBrowser ;
            public bool WebView ;
        }
        public WebView(ReadOnlyTargetRules Target) : base(Target)
        {
            CheckLicense(Path.GetDirectoryName(Target.ProjectFile.ToString()));
            gen_template();
            PublicDependencyModuleNames.AddRange(
                new string[]{
                    "Slate",
                    "SlateCore",
                    "Core",
                    "CoreUObject",
                    "UMG",
                    "Projects",
                    "Engine",
                    "ApplicationCore",
                    "RHI",
                    "RenderCore",
                    "InputCore",
                    "Serialization",
                    "MediaUtils",
                    "OpenSSL",
                    "MatureJson",
                    "BaseBrowser",
                    "ImageWrapper",
                    "AudioMixer",
                    "AudioExtensions"
                }
            );
            if (Target.bBuildEditor) { 
                PublicDependencyModuleNames.AddRange(
                    new string[]{
                        "WorkspaceMenuStructure",
                        "ToolMenus"
                    }
                );
            }
            // 
            Int32 ue_version = Target.Version.MajorVersion * 10000 + Target.Version.MinorVersion * 100 + Target.Version.PatchVersion;
            // After version 5.4, the official mall plugin can only have one platform architecture. 
            //
            if (50100 <= ue_version && Target.Platform == UnrealTargetPlatform.Android && CanSupportAndroid())
            {//
                Console.WriteLine("WEBVIEW_ANDROID ... ");
                PublicDefinitions.Add("WEBVIEW_ANDROID=1"); //
                PublicDefinitions.Add("DISABLE_WARNINGS");
                PrivateDependencyModuleNames.Add("AndroidBrowser");
            }
            else if(false==InDev() && (Target.Configuration == UnrealTargetConfiguration.DebugGame
                || Target.Configuration == UnrealTargetConfiguration.Debug
                || (ue_version < 50700 && project_bridge_status()) ))
            {
                PublicDefinitions.Add("USING_WEBBROWSER=1"); //
                PrivateDependencyModuleNames.Add("WebBrowser");
                Console.WriteLine("UnrealTargetPlatform USING_WEBBROWSER ...... bridge or debug ");
            }
            //else if (Target.Platform == UnrealTargetPlatform.Mac ||
            //    Target.Platform == UnrealTargetPlatform.TVOS ||
            //    Target.Platform == UnrealTargetPlatform.IOS)
            //{//
            //    Console.WriteLine("WEBVIEW_APPLE");
            //    PublicDefinitions.Add("WEBVIEW_APPLE=1"); //
            //    PublicDependencyModuleNames.Add("AppleBrowser");
            //}
            else if(can_cef_browser(ue_version))
            {//
                Console.WriteLine("WEBVIEW_CEF  ");
                //Console.WriteLine("WEBVIEW Architectures " + Target.Architectures.ToString());
                if (Target.Type != TargetType.Server && Target.Platform == UnrealTargetPlatform.Win64)
                {
                    AddEngineThirdPartyPrivateStaticDependencies(Target, "DX12");
                    PrivateIncludePathModuleNames.Add("SlateRHIRenderer");
                    DynamicallyLoadedModuleNames.Add("SlateRHIRenderer");
                    PublicSystemLibraries.AddRange(
                        new string[] { "comsuppw.lib", "dxgi.lib", "d3d11.lib", "d3d12.lib" });
                    PublicDependencyModuleNames.AddRange(
                        new string[] { "DX11", "DX12", "D3D11RHI", "D3D12RHI" });
                }
                PublicDependencyModuleNames.Add("cefForUe");
                PublicDependencyModuleNames.Add("CefBase");
                PublicDependencyModuleNames.Add("CefBrowser");
            }
            else 
            {
                PublicDefinitions.Add("USING_WEBBROWSER=1"); //
                PrivateDependencyModuleNames.Add("WebBrowser");
                Console.WriteLine("UnrealTargetPlatform USING_WEBBROWSER ...... ");
            }
            if (Target.bBuildEditor == true)
            {
                PrivateIncludePathModuleNames.Add("UnrealEd");
                PrivateDependencyModuleNames.Add("UnrealEd");
            }
            PublicDependencyModuleNames.Add("MatureJson");
            PublicDependencyModuleNames.Add("BaseBrowser");
        }
        bool project_bridge_status()
        {
            ProjectDescriptor project_desc = ProjectDescriptor.FromFile(Target.ProjectFile);
            foreach (PluginReferenceDescriptor plugin in project_desc.Plugins)
            {
                if (plugin.Name == "Bridge")
                {
                    return plugin.bEnabled;
                }
            }
            return bridge_defualt_status("Bridge");
        }
        bool bridge_defualt_status(string plugin_name)
        {// 
            string PluginPath = Path.Combine(EngineDirectory,"Plugins");
            foreach (string FileName in Directory.EnumerateFiles(PluginPath, plugin_name + ".uplugin", SearchOption.TopDirectoryOnly))
            {
                FileReference pluginFile = new FileReference(FileName);
                PluginInfo Plugin = new PluginInfo(pluginFile, PluginType.Engine);
                if (!Plugin.Descriptor.bEnabledByDefault.HasValue) continue;
                if (Plugin.Descriptor.bEnabledByDefault == true) {
                    return true;
                }
            }
            return false;
        }

        bool can_cef_browser(int ue_version)
        {//
            string platform = Target.Platform.ToString();
            if (Directory.Exists(Path.Combine(PluginDirectory, "Source", "CefBrowser"))) {
                // Compile the source code
                return (Target.Platform == UnrealTargetPlatform.Linux ||
                Target.Platform == UnrealTargetPlatform.Win64 ||
                (Target.Platform == UnrealTargetPlatform.Mac && 50400 <= ue_version) ||
                platform == "LinuxArm64" ||
                platform == "LinuxAArch64") ;
            }

            return  Directory.Exists(Path.Combine(PluginDirectory, "Source", "ThirdParty", "CefBrowser", "Binaries", platform));
        }

        bool isDependPlugin(string plugin)
        {
            bool hasDep = false;
            FileReference pluginFile = new FileReference(Path.Combine(PluginDirectory, "WebView.uplugin"));
            PluginInfo Plugin = new PluginInfo(pluginFile, PluginType.Project);
            foreach (PluginReferenceDescriptor desc in Plugin.Descriptor.Plugins) {
                if (desc.Name != plugin) continue;
                hasDep = desc.bEnabled;
                break;
            }
            return hasDep;
        }

        void CheckLicense(string ProjectDir)
        {
            string licensePath = Path.Combine(ProjectDir, "Content", "license");
            if (!Directory.Exists(licensePath))
            {
                Directory.CreateDirectory(licensePath);
            }
            string GamePath = Path.Combine(ProjectDir, "Config");
            string GameCfg = Path.Combine(GamePath, "DefaultGame.ini");
            if (!Directory.Exists(GamePath))
            {
                Directory.CreateDirectory(GamePath);
            }
            if (!File.Exists(GameCfg))
            {
                File.Create(GameCfg);
            }
            string content;
            try { content = File.ReadAllText(GameCfg/*, Encoding.UTF8*/); }
            catch
            {//
                return;
            }
            string licenseDst = "+DirectoriesToAlwaysStageAsUFS=(Path=\"license\")";
            string licenseSrc = "-DirectoriesToAlwaysStageAsUFS=(Path=\"license\")";
            string licenseNode = "[/Script/UnrealEd.ProjectPackagingSettings]";

            if (content.Contains(licenseNode))
            {
                if (content.Contains(licenseDst))
                {
                    Console.WriteLine(GameCfg + " has configure!");
                    return;//
                }
                else if (content.Contains(licenseSrc))
                {
                    content = content.Replace(licenseSrc, licenseDst + "\n");
                }
                else
                    content = content.Replace(licenseNode, licenseNode + "\n" + licenseDst);
            }
            else
            {
                content += "\n\n" + licenseNode + "\n" + licenseDst;
            }
            File.WriteAllText(GameCfg, content, Encoding.UTF8);
            Console.WriteLine(GameCfg + " auto configure!");
        }
        void gen_template()
        {
            bool isUsingJson = false;
            string RootPath = ModuleDirectory;
            string subfix = ".template-del";
            foreach (string filePath in Directory.EnumerateFiles(RootPath, "*" + subfix, SearchOption.AllDirectories))
            {
                string FileName = Path.GetFileName(filePath);
                string pathDst = filePath.Replace(FileName, FileName.Replace(subfix, ""));
                string srcContent;
                srcContent = File.ReadAllText(filePath);
                if (isUsingJson)
                {// create new file
                    srcContent = srcContent.Replace("//@TEMPLATE", "");
                }
                if (!File.Exists(pathDst))
                {// don't exists will write
                    //FileStream stream=File.Open(pathDst, FileMode.Truncate);
                    File.WriteAllText(pathDst, srcContent);
                    continue;
                }
                // check content is eq
                string dstContent = File.ReadAllText(pathDst);
                if (srcContent.GetHashCode() == dstContent.GetHashCode())
                {
                    continue;
                }
                File.WriteAllText(pathDst, srcContent);
            }

        }
		bool InDev(){
            // for development env
            if (Directory.Exists(Path.Combine(ModuleDirectory, "..", "AndroidBrowser"))
                || Directory.Exists(Path.Combine(ModuleDirectory, "..", "CefBrowser")))
                return true;
            return false;
		}
        bool CanSupportAndroid()
        {
            if (InDev())
                return true;
            // in plugin pkg
            return Directory.Exists(Path.Combine(ModuleDirectory, "..", "ThirdParty", "AndroidBrowser", "Binaries"));
        }

    }
}
