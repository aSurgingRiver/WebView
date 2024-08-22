// Copyright aXiuShen. All Rights Reserved.

#include "cef3lib.h"
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

//
//#if defined CEF_WINDOWS
//#define CEFLIB_EXPORT __declspec(dllimport)
//#elif defined CEF_LINUX
//#define CEFLIB_EXPORT 
//#endif
//#ifdef __cplusplus
//extern "C" {
//#endif
//	CEFLIB_EXPORT const char* cef_api_hash(int entry);
//#ifdef __cplusplus
//}
//#endif
//
//void CefEnableHighDPISupport();
#if defined CEF_MAC
#	include "include/wrapper/cef_library_loader.h"
#endif
// WEB_CORE_API
#ifdef WEBVIEW_CUSTOMIZED_CORE
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

#if defined CEF_MAC
	CefScopedLibraryLoader CEFLibraryLoader;
#endif
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
	return CEF3_BRANCH;
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
		UE_LOG(LogTemp, Fatal, TEXT("Failed to get CEF3 DLL handle for %s: %s (%d)"), *Path, ErrorMsg, ErrorNum);
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
#if defined CEF_WINDOWS
	LibPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/cefForUe"), TEXT(CEF3_VERSION), TEXT("win64/lib"));
#elif defined CEF_MAC
	LibPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/cefForUe"), TEXT(CEF3_VERSION), TEXT("mac/lib"));
#elif defined CEF_LINUX
	LibPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/cefForUe"), TEXT(CEF3_VERSION), TEXT("linux/lib"));
#endif
	return LibPath;
}

void CEF3LIB::LoadCEF3Modules()
{
	if (dllHand.size())return;// has load
	//UE_LOG(WebViewLog, Error, TEXT("CEF3DLL::LoadCEF3Modules"));
	FString libPath = LibPath();
#if defined CEF_WINDOWS
	FString envPath = FPlatformMisc::GetEnvironmentVariable(TEXT("Path")) + TEXT(";") + libPath;
	FPlatformMisc::SetEnvironmentVar(TEXT("Path"), *envPath);
	FPlatformProcess::PushDllDirectory(*libPath);
	if (LoadDllCEF(FPaths::Combine(*libPath, TEXT("chrome_elf.dll")))) {
		LoadDllCEF(FPaths::Combine(*libPath, TEXT("libcef.dll")));
	}
	FPlatformProcess::PopDllDirectory(*libPath);
#elif defined CEF_MAC
	FString envPath = FPlatformMisc::GetEnvironmentVariable(TEXT("LD_LIBRARY_PATH")) + TEXT(":") + libPath;
	FPlatformMisc::SetEnvironmentVar(TEXT("LD_LIBRARY_PATH"), *envPath);
	FString frameWorks = FPaths::Combine(*libPath, TEXT("Chromium Embedded Framework.framework"), TEXT("Chromium Embedded Framework"));
	if (!cef_load_library(TCHAR_TO_ANSI(*frameWorks))) {
		UE_LOG(LogTemp, Error, TEXT("Chromium loader initialization failed"));
	}
#elif defined CEF_LINUX
	FString envPath = FPlatformMisc::GetEnvironmentVariable(TEXT("LD_LIBRARY_PATH")) + TEXT(":") + libPath;
	FPlatformMisc::SetEnvironmentVar(TEXT("LD_LIBRARY_PATH"), *envPath);
#endif
}

void CEF3LIB::UnloadCEF3Modules()
{
	for (auto it = dllHand.rbegin(); it != dllHand.rend(); it++) {
		FPlatformProcess::FreeDllHandle(*it);
	}
	dllHand.clear();
}
#endif

