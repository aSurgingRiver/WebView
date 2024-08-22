// Copyright aXiuShen. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Text;
using System.Collections.Generic;

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
        MergeFile(ModuleDirectory);
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
            for (int index = 1; index <= kvp.Value.Count; index++)
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
