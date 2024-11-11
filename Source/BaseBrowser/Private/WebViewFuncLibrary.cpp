// Copyright aXiuShen. All Rights Reserved.

#include "WebViewFuncLibrary.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Framework/Application/SlateApplication.h"
#include "Developer/DesktopPlatform/Public/IDesktopPlatform.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"

FString UWebViewFuncLibrary::OpenDirectoryDialog(FString title, FString default_path) {
	if (title.IsEmpty()) {
		title = TEXT("Open Folder");
	}
	auto window = FSlateApplication::Get().GetActiveTopLevelWindow();
	auto osWindow = window->GetNativeWindow()->GetOSWindowHandle();
	FString outPath;
	FDesktopPlatformModule::Get()->OpenDirectoryDialog(osWindow, title, default_path, outPath);
	return outPath;
}

FString UWebViewFuncLibrary::OpenFileDialog(FString title, FString default_path) {
	if (title.IsEmpty()) {
		title = TEXT("Open File");
	}
	auto window = FSlateApplication::Get().GetActiveTopLevelWindow();
	auto osWindow = window->GetNativeWindow()->GetOSWindowHandle();
	FString outPath;//None Multiple
	TArray<FString> OutFilenames;
	FDesktopPlatformModule::Get()->OpenFileDialog(osWindow, title, default_path,TEXT(""), TEXT(""), EFileDialogFlags::None, OutFilenames);
	if (OutFilenames.Num())return OutFilenames[0];
	return FString();
}

FString UWebViewFuncLibrary::SaveFileDialog(FString title, FString default_path) {
	if (title.IsEmpty()) {
		title = TEXT("Save File");
	}
	auto window = FSlateApplication::Get().GetActiveTopLevelWindow();
	auto osWindow = window->GetNativeWindow()->GetOSWindowHandle();
	TArray<FString> OutFilenames;
	FDesktopPlatformModule::Get()->SaveFileDialog(osWindow, title, default_path, TEXT(""), TEXT(""), EFileDialogFlags::None, OutFilenames);
	if (OutFilenames.Num())return OutFilenames[0];
	return FString();
}

TArray<FString> UWebViewFuncLibrary::OpenFilesDialog(FString title, FString default_path) {
	if (title.IsEmpty()) {
		title = TEXT("Open Files");
	}
	auto window = FSlateApplication::Get().GetActiveTopLevelWindow();
	auto osWindow = window->GetNativeWindow()->GetOSWindowHandle();
	TArray<FString> OutFilenames;
	FDesktopPlatformModule::Get()->OpenFileDialog(osWindow, title, default_path, TEXT(""), TEXT(""), EFileDialogFlags::Multiple, OutFilenames);
	return OutFilenames;
}



//virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;
//virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex) override;
//virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;
//virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName) override;
