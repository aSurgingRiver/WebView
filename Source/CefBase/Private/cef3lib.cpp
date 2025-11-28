// Copyright aXiuShen. All Rights Reserved.

#include "cef3lib.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#include "Windows/WindowsPlatformMisc.h"
#elif PLATFORM_LINUX
#include "Linux/LinuxPlatformProcess.h"
#include "Linux/LinuxPlatformMisc.h"
#elif PLATFORM_MAC
#include "Mac/MacPlatformProcess.h"
#include "Mac/MacPlatformMisc.h"
#endif
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Interfaces/IPluginManager.h"
#include "WebViewLog.h"
#include <string>
#include <stdlib.h>
#ifdef WEBVIEW_CEF
// WEB_CORE_API
#include "include/cef_version.h"
#if 6943<=CEF3_BRANCH
#include "include/cef_version_info.h"
#endif
#endif

// WEB_CORE_API
class CEF3LIB: public ICEF3LIB {
public:
	void LoadCEF3Modules() ;
	void UnloadCEF3Modules() ;
	int Branch();
	FString LibPath() ;
	virtual ~CEF3LIB() = default;
private:
	void* LoadDllCEF(const FString& Path);
private:
	std::vector<void*> dllHand;

};

ICEF3LIB* ICEF3LIB::get() {
	static ICEF3LIB* install= nullptr;
	//UE_LOG(WebViewLog, Error, TEXT("CEF3DLL::get"));
	if (nullptr == install) {
		install = new CEF3LIB();
	}
	return install;
}
int CEF3LIB::Branch() {
#ifdef WEBVIEW_CEF
	return CEF3_BRANCH;
#else
	return 0;
#endif
}

void* CEF3LIB::LoadDllCEF(const FString& Path)
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
		UE_LOG(WebViewLog, Fatal, TEXT("Failed to get CEF3 DLL handle for %s: %s (%d)"), *Path, ErrorMsg, ErrorNum);
	}
	else {
		dllHand.push_back(Handle);
	}
	return Handle;
}

FString CEF3LIB::LibPath() {
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("CefBase"));
	if (!Plugin.IsValid()) {
		Plugin = IPluginManager::Get().FindPlugin(TEXT("WebView"));
	}
	const FString BaseDir = FPaths::ConvertRelativePathToFull(Plugin->GetBaseDir());
	FString LibPath;
#ifdef WEBVIEW_CEF
	LibPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/cefForUe"), TEXT(CEF3_VERSION), TEXT(CEF3_ARCH), TEXT("lib"));
#endif
	return LibPath;
}

void CEF3LIB::LoadCEF3Modules()
{
	if (dllHand.size())return;// has load
#if 50700<=WEBVIEW_ENGINE_VERSION
	return;
#endif

#ifdef WEBVIEW_CEF
	//UE_LOG(WebViewLog, Error, TEXT("CEF3DLL::LoadCEF3Modules"));
	FString libPath = LibPath();
#if PLATFORM_WINDOWS
	FString envPath = FPlatformMisc::GetEnvironmentVariable(TEXT("Path")) + TEXT(";") + libPath;
	FPlatformMisc::SetEnvironmentVar(TEXT("Path"), *envPath);
	FPlatformProcess::PushDllDirectory(*libPath);
	if (LoadDllCEF(FPaths::Combine(*libPath, TEXT("chrome_elf.dll")))) {
		LoadDllCEF(FPaths::Combine(*libPath, TEXT("libcef.dll")));
	}
	FPlatformProcess::PopDllDirectory(*libPath);
#endif

#if !PLATFORM_MAC
	int cef_version_major = cef_version_info(0);
	int cef_version_minor = cef_version_info(1);
	int cef_version_patch = cef_version_info(2);
	int cef_commit_number = cef_version_info(3);
	int chrome_version_major = cef_version_info(4);
	int chrome_version_minor = cef_version_info(5);
	int chrome_version_build = cef_version_info(6);
	int chrome_version_patch = cef_version_info(7);
	UE_LOG(WebViewLog, Log,
		TEXT("cef_version_major:%d cef_version_minor:%d cef_version_patch:%d cef_commit_number:%d chrome_version_major:%d chrome_version_minor:%d chrome_version_build:%d chrome_version_patch:%d ")
		, cef_version_major, cef_version_minor, cef_version_patch, cef_commit_number, chrome_version_major, chrome_version_minor, chrome_version_build, chrome_version_patch);
#endif
#endif
}

void CEF3LIB::UnloadCEF3Modules()
{
	for (auto it = dllHand.rbegin(); it != dllHand.rend(); it++) {
		FPlatformProcess::FreeDllHandle(*it);
	}
	dllHand.clear();
}

