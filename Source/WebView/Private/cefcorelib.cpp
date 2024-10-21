// Copyright aXiuShen. All Rights Reserved.

#include "cefcorelib.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#if defined CEF_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#include "Windows/WindowsPlatformMisc.h"
#elif defined CEF_LINUX
#include "Linux/LinuxPlatformProcess.h"
#include "Linux/LinuxPlatformMisc.h"
#elif defined CEF_MAC
#include "Mac/MacPlatformProcess.h"
#include "Mac/MacPlatformMisc.h"
#endif
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include <string>
#include <stdlib.h>
// WEB_CORE_API

// WEB_CORE_API
#ifdef WEBVIEW_CEF
class CefCoreLIB : public ICefCoreLIB {
public:
	bool can_load();
	void Load() ;
	void Unload() ;
	FString LibPath() ;
	CefCoreLIB();
	virtual ~CefCoreLIB() = default;
private:
	void* LoadOne(const FString& Path);
private:
	std::vector<void*> dllHand;

#if defined CEF_MAC
	CefScopedLibraryLoader CEFLibraryLoader;
#endif
};

ICefCoreLIB* ICefCoreLIB::get() {
	static ICefCoreLIB* install= nullptr;
	//UE_LOG(WebViewLog, Error, TEXT("CEF3DLL::get"));
	if (nullptr == install) {
		install = new CefCoreLIB();
	}
	return install;
}

void* CefCoreLIB::LoadOne(const FString& Path)
{
	if (Path.IsEmpty())
	{
		return nullptr;
	}
	void* Handle = FPlatformProcess::GetDllHandle(*Path);
	if (!Handle)
	{
		int32 ErrorNum = FPlatformMisc::GetLastError();
		TCHAR ErrorMsg[1024];
		FPlatformMisc::GetSystemErrorMessage(ErrorMsg, 1024, ErrorNum);
		UE_LOG(LogTemp, Fatal, TEXT("Failed to get CEF3 DLL handle for %s: %s (%d)"), *Path, ErrorMsg, ErrorNum);
	}
	else {
		dllHand.push_back(Handle);
	}
	return Handle;
}

CefCoreLIB::CefCoreLIB() {
}

bool CefCoreLIB::can_load() {
#ifdef USING_WEBBROWSER
	return false;
#else
	return true;
#endif
}

FString CefCoreLIB::LibPath() {
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("WebView"));
	//if (!Plugin.IsValid()) {
	//	Plugin = IPluginManager::Get().FindPlugin(TEXT("WebView"));
	//}
	FString BaseDir = FPaths::ConvertRelativePathToFull(Plugin->GetBaseDir());
	BaseDir = FPaths::Combine(*BaseDir, TEXT("Source"), TEXT("ThirdParty"), TEXT("CefBrowser"), TEXT("Binaries"));
	FString LibPath;
#if defined CEF_WINDOWS
	LibPath = FPaths::Combine(*BaseDir, TEXT("Win64"), TEXT("Editor"));
#elif defined CEF_MAC
	LibPath = FPaths::Combine(*BaseDir, TEXT("Mac"), TEXT("Editor"));
#elif defined CEF_LINUX
	LibPath = FPaths::Combine(*BaseDir, TEXT("Linux"), TEXT("Editor"));
#endif
	return LibPath;
}

void CefCoreLIB::Load()
{
	if (dllHand.size())return;// has load
	//UE_LOG(WebViewLog, Error, TEXT("CEF3DLL::LoadCEF3Modules"));
	FString libPath = LibPath();
	if (!FPaths::DirectoryExists(*libPath))return ;

	FString envPath = FPlatformMisc::GetEnvironmentVariable(TEXT("Path")) + TEXT(";") + libPath;
	FPlatformMisc::SetEnvironmentVar(TEXT("Path"), *envPath);
	FPlatformProcess::PushDllDirectory(*libPath);
	//FModuleManager::Get().AddBinariesDirectory(*libPath, true);
	std::vector<FString> vdir;
	vdir.push_back(libPath);
	auto visitfunc = [this,&vdir](const TCHAR* fileOrDir, bool isDir)->bool {
		if (isDir) {
			vdir.push_back(fileOrDir);
			return true;
		}
		FString FileN = fileOrDir;
		if (!FileN.EndsWith(TEXT(".dll")))return true;
		if (!FileN.Contains(TEXT("CefBrowser"))) return true;
		LoadOne(FPaths::Combine(*FileN));
		return true;
    };
	for (int vdir_pos = 0; vdir_pos < vdir.size(); vdir_pos++) {
		FString one_dir = vdir[vdir_pos];
		if (!FPaths::DirectoryExists(*one_dir))continue;
		IFileManager::Get().IterateDirectory(*one_dir, visitfunc);
	}

	FPlatformProcess::PopDllDirectory(*libPath);
}

void CefCoreLIB::Unload()
{
	for (auto it = dllHand.rbegin(); it != dllHand.rend(); it++) {
		FPlatformProcess::FreeDllHandle(*it);
	}
	dllHand.clear();
}
#endif

