using UnrealBuildTool;
using System;
using System.IO;
using System.Text;
using System.Diagnostics;
using System.Collections.Generic;
using System.IO.Compression;
using System.Runtime.InteropServices;

public class WebBuildGuide : ModuleRules
{
	public WebBuildGuide(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		bool isLicenseToPak = true;
		//Console.WriteLine("===============================");
		//Console.WriteLine("Target.Architecture" + Target.Architecture);
		//string sourcePath = Path.Combine(ModuleDirectory, "..");
		string pluginPath = PluginDirectory;// Path.Combine(sourcePath, "..", "..");
		CopyDir(".lng", Path.Combine(ModuleDirectory, "language", "Binaries.lng"), Path.Combine(pluginPath, "Binaries"));
        CopyDir(".lng", Path.Combine(ModuleDirectory, "language", "Intermediate.lng"), Path.Combine(pluginPath, "Intermediate"));
        string projFile = Target.ProjectFile.ToString();
		if (Target.Version.MajorVersion >= 5)
		{
			CopyCefBrowser(pluginPath, projFile, "UnrealGame", "" + Target.Configuration, Target);
			CopyCefBrowser(pluginPath, projFile, "UnrealGame", "Inc", Target);
		}
		else
		{
			CopyCefBrowser(pluginPath, projFile, "UE4", "" + Target.Configuration, Target);
		}
		CheckLicense(Path.GetDirectoryName(projFile), isLicenseToPak);
		if (Target.Version.MajorVersion >= 5 && Target.Platform == UnrealTargetPlatform.Linux)
		{
			MakeSymLink(projFile);
		}
	}

	void MakeSymLink(string projectFile)
	{
		String binariesP = Path.Combine(PluginDirectory, "Binaries", "Linux");
		//Console.WriteLine("binariesP=" + binariesP);
		string binCef = Path.Combine(binariesP, "libcef.so");
		String libcefP = "";
		foreach (string lib in Directory.EnumerateFiles(Path.Combine(Path.GetDirectoryName(projectFile), "Plugins"), "libcef.so", SearchOption.AllDirectories))
		{
			if (binCef == lib) continue;
			if (!lib.Contains("CefBase")) continue;
            if (!lib.Contains("linux/lib")) continue;
            //Console.WriteLine("FileName=" + lib);
            libcefP = lib;
			break;
		}
		if (libcefP == "") return;
		if (!Directory.Exists(binariesP))
		{
			Directory.CreateDirectory(binariesP);
        }
        RuntimeDependencies.Add(binCef, libcefP);
        //Console.WriteLine("cmd =cd \"" + binariesP + "\"; ln \"" + BinP + CefP + "\" libcef.so");
        //RuntimeDependencies.Add(binCef);
    }


	void CopyCefBrowser(string pluginPath, string projectFile, string sw, string config, ReadOnlyTargetRules Target)
	{
		//string projName = Path.GetFileName(projectFile).Replace(".uproject", "");// 
		string targetName = Target.Name;
		string projPath = Path.GetDirectoryName(projectFile); // 
		string srcMatch = Path.Combine(sw, config, "CefBrowser");
		//string dstMatch = Path.Combine(projName, config, "CefBrowser");
		string dstMatch = Path.Combine(targetName, config, "CefBrowser");
		string pluginInter = Path.Combine(pluginPath, "Intermediate");
		//Console.WriteLine("projName=" + projName);
		//Console.WriteLine("projPath=" + projPath);
		//Console.WriteLine("srcMatch=" + srcMatch);
		//Console.WriteLine("dstMatch=" + dstMatch);
		if (!Directory.Exists(pluginInter)) return;
		foreach (string pathName in Directory.EnumerateDirectories(pluginInter, "CefBrowser", SearchOption.AllDirectories))
		{
			//Console.WriteLine("pathName=" + pathName);
			if (!pathName.EndsWith(srcMatch)) continue;
			//Console.WriteLine("pathNameff=" + pathName);
			foreach (string FileName in Directory.EnumerateFiles(pathName, "*.*", SearchOption.AllDirectories))
			{
				string name = Path.GetFileName(FileName);// 
				string srcBrowserPath = Path.GetDirectoryName(FileName);// 
				string dstBrowserPath = srcBrowserPath.Replace(pluginPath, projPath);//.Replace(srcMatch, dstMatch);
				if (!dstBrowserPath.Contains(Path.Combine("" + Target.Architecture, srcMatch))) dstBrowserPath = dstBrowserPath.Replace(srcMatch, dstMatch);
				string dstFile = Path.Combine(dstBrowserPath, name);
				//Console.WriteLine("srcBrowserPath=" + srcBrowserPath);
				//Console.WriteLine("dstBrowserPath=" + dstBrowserPath);
				//Console.WriteLine("dstFile=" + dstFile);
				if (!Directory.Exists(dstBrowserPath))
				{
					Directory.CreateDirectory(dstBrowserPath);
				}
				if (File.Exists(dstFile))
				{
					File.SetAttributes(dstFile, FileAttributes.Normal);
				}
				System.IO.File.Copy(FileName, dstFile, true);
				//Console.WriteLine("FileName=" + FileName);
				//Console.WriteLine("dstFile=" + dstFile);
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

	void CheckLicense(string ProjectDir, bool isLicensePak)
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
		if (!Directory.Exists(GamePath))
		{
			Directory.CreateDirectory(GamePath);
		}
		if (!File.Exists(GameCfg))
		{
			File.Create(GameCfg);
		}
		//if( File.OpenWrite(GameCfg)) return ;
		string content;
		try { content = File.ReadAllText(GameCfg/*, Encoding.UTF8*/); }
		catch
		{//
			return;
		}
		string licenseSrc = "+DirectoriesToAlwaysStageAsUFS=(Path=\"license\")";
		string licenseDst = "-DirectoriesToAlwaysStageAsUFS=(Path=\"license\")";
		string licenseNode = "[/Script/UnrealEd.ProjectPackagingSettings]";
		if (isLicensePak)//add
		{
			string licensePkg = licenseSrc;
			licenseSrc = licenseDst;
			licenseDst = licensePkg;
		}
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
			else if (isLicensePak)
				content = content.Replace(licenseNode, licenseNode + "\n" + licenseDst);
		}
		else if (isLicensePak)
		{
			content += "\n\n" + licenseNode + "\n" + licenseDst;
		}
		else return;
		File.WriteAllText(GameCfg, content, Encoding.UTF8);
		Console.WriteLine(GameCfg + " auto configure!");
	}
}
