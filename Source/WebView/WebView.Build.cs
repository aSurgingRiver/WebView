// Copyright aSurgingRiver, Inc. All Rights Reserved.

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
        public WebView(ReadOnlyTargetRules Target) : base(Target)
        {
            bool isUsingJson = false;
            if (isDependPlugin("JsonLibrary"))
            {// use for JsonLibaray
                isUsingJson = true;
                PublicDefinitions.Add("JSON_LIB"); //add custom MICRO
                PublicDependencyModuleNames.Add("JsonLibrary");
            }
            if (isDependPlugin("CefBase") && !CheckVersion(Target)) { 
                Console.WriteLine("CefBase and WebView version mismatch ...... ");
                throw new InvalidOperationException("CefBase and WebView version mismatch");
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
                    "Core",
                    "CoreUObject",
                    "Slate",
                    "SlateCore",
                    "UMG",
                    "Engine",
                    "WebBuildGuide"
                }
            );

            if (Target.Platform == UnrealTargetPlatform.Win64
                || Target.Platform == UnrealTargetPlatform.Linux
                || Target.Platform == UnrealTargetPlatform.Mac)
            {//
                PublicDependencyModuleNames.Add("CefBase"); 
                PublicDependencyModuleNames.Add("CefBrowser"); 
                PublicDefinitions.Add("CEF_NEW_VERSION=1"); //
            }
            else {//  WebBrowser
                PrivateDependencyModuleNames.Add("ProxyWeb");
                PublicDefinitions.Add("CEF_NEW_VERSION=0"); //
            }
            if (Target.bBuildEditor == true) {
                PrivateIncludePathModuleNames.AddRange(
                    new string[] {
                        "UnrealEd",
                    }
                );
                PrivateDependencyModuleNames.AddRange(
                    new string[] {
                        "UnrealEd",
                    }
                );
            }
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
        int ReadVersion(string plugin)
        {
            FileReference pluginFile = new FileReference(plugin);
            PluginInfo Plugin = new PluginInfo(pluginFile, PluginType.Project);
            string version = Plugin.Descriptor.VersionName;
            if (version.Contains("."))
                version = Plugin.Descriptor.MarketplaceURL;
            try {
                return Convert.ToInt32(version.Replace(" ", ""));
            }
            catch (Exception e) { 
            }
            return 0x7FFFFFFF;
            //return ;
        }
        bool CheckVersion(ReadOnlyTargetRules Target) {
            string projPath = Path.GetDirectoryName(Target.ProjectFile.ToString()); //
            if (!PluginDirectory.Contains(projPath)) projPath = Path.GetDirectoryName(PluginDirectory);
            int CefBase = 0;
            int WebView = 0x7FFFFFFF;
            foreach (string pluginFile in Directory.EnumerateFiles(projPath, "*.uplugin", SearchOption.AllDirectories))
            {
                if (pluginFile.Contains("CefBase.uplugin")) CefBase = ReadVersion(pluginFile);
                else if (pluginFile.Contains("WebView.uplugin")) WebView = ReadVersion(pluginFile);
            }
            Console.WriteLine("CefBase = " + CefBase);
            Console.WriteLine("WebView = " + WebView);
            return WebView <= CefBase;
        }
    }
}
