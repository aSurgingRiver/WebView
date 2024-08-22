// Copyright aXiuShen. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Text;

public class CefBrowser : ModuleRules
{
    public CefBrowser(ReadOnlyTargetRules Target) : base(Target)
    {
        CheckLicense(Path.GetDirectoryName(Target.ProjectFile.ToString()));
        Type = ModuleType.External;
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
        string LibType;
        if (Target.bBuildEditor == true)
        {
            LibType = "Editor";
        }
        else if (Target.Configuration == UnrealTargetConfiguration.Development ||
            Target.Configuration == UnrealTargetConfiguration.Shipping)
        {
            LibType = Target.Configuration.ToString();
        }
        else
        {
            return;
        }
        string platform_bin = Path.Combine(ModuleDirectory, "Binaries", Target.Platform.ToString(), LibType);

        if (!Directory.Exists(platform_bin)) Directory.CreateDirectory(platform_bin);
        foreach (string FileName in Directory.EnumerateFiles(platform_bin, "*.lib", SearchOption.TopDirectoryOnly))
        {
            PublicAdditionalLibraries.Add(FileName);
        }
        foreach (string FileName in Directory.EnumerateFiles(platform_bin, "*.dll", SearchOption.TopDirectoryOnly))
        {
            PublicDelayLoadDLLs.Add(System.IO.Path.GetFileName(FileName));
            RuntimeDependencies.Add(FileName);
        }
        foreach (string FileName in Directory.EnumerateFiles(platform_bin, "*.so", SearchOption.TopDirectoryOnly))
        {
            PublicAdditionalLibraries.Add(FileName);
        }
        foreach (string FileName in Directory.EnumerateFiles(platform_bin, "*.a", SearchOption.TopDirectoryOnly))
        {
            PublicAdditionalLibraries.Add(FileName);
        }

        return;
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

}
