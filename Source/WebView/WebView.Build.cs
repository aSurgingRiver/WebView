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
using Tools.DotNETCommon;

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
            bool isUsingJson = false;
            if (isDependPlugin("JsonLibrary"))
            {// use for JsonLibaray
                isUsingJson = true;
                PublicDefinitions.Add("JSON_LIB"); //add custom MICRO
                PublicDependencyModuleNames.Add("JsonLibrary");
            }
            string RootPath = ModuleDirectory;
            string subfix = ".template";
            foreach (string filePath in Directory.EnumerateFiles(RootPath, "*"+subfix, SearchOption.AllDirectories))
            {
                string FileName = Path.GetFileName(filePath);
                string pathDst = filePath.Replace(FileName, FileName.Replace(subfix, ""));
                string srcContent;
                srcContent = File.ReadAllText(filePath);
                if (isUsingJson) {// create new file
                    srcContent = srcContent.Replace("//@TEMPLATE","");
                }
                if (!File.Exists(pathDst)) {// don't exists will write
                    //FileStream stream=File.Open(pathDst, FileMode.Truncate);
                    File.WriteAllText(pathDst, srcContent);
                    continue;
                }
                // check content is eq
                string dstContent = File.ReadAllText(pathDst);
                if (srcContent.GetHashCode() == dstContent.GetHashCode()) {
                    continue;
                }
                File.WriteAllText(pathDst, srcContent);
            }

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
                    "ImageWrapper"
                }
            );
            if (project_bridge_status())
            {
                PublicDefinitions.Add("USING_WEBBROWSER=1"); //
                PrivateDependencyModuleNames.Add("WebBrowser");
                Console.WriteLine("project_no_load_webview ...... ");
            }
            else if (!((Target.Platform == UnrealTargetPlatform.Linux ||
                Target.Platform == UnrealTargetPlatform.Win64)))
            {
                PublicDefinitions.Add("USING_WEBBROWSER=1"); //
                PrivateDependencyModuleNames.Add("WebBrowser");
                Console.WriteLine("UnrealTargetPlatform USING_WEBBROWSER ...... ");
            }

            else
            {//
                Console.WriteLine("WEBVIEW_CUSTOMIZED_CORE  ");
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
            if (Target.bBuildEditor == true)
            {
                PrivateIncludePathModuleNames.Add("UnrealEd");
                PrivateDependencyModuleNames.Add("UnrealEd");
            }
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
    }
}
