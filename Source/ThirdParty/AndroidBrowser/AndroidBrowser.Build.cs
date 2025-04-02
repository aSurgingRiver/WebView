// Copyright aXiuShen. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;
using System.Text;
using System.Collections.Generic;

public class AndroidBrowser : ModuleRules
{
    public AndroidBrowser(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        PublicDefinitions.Add("WEBVIEW_ANDROID=1"); //
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
        string LibType;
        string platform_bin;
        if (Target.bBuildEditor == true)
        {
            return ;
        }
        
        if (Target.Configuration == UnrealTargetConfiguration.Development ||
            Target.Configuration == UnrealTargetConfiguration.Shipping)
        {
            LibType = Target.Configuration.ToString();
        }
        else
        {
            return;
        }
        String arch = "";
        if (Target.Architecture == UnrealArch.X64)
        {
            arch = "x";
        }
        else {
            arch = "a";
        }
        MergeFile(ModuleDirectory);
        // AndroidBrowser\Binaries\Android\Development\a
        platform_bin = Path.Combine(ModuleDirectory, "Binaries", "Android", LibType,arch);
        if (!Directory.Exists(platform_bin)) Directory.CreateDirectory(platform_bin);
        foreach (string FileName in Directory.EnumerateFiles(platform_bin, "*.a", SearchOption.AllDirectories))
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
}
