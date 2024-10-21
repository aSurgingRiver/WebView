// Copyright aXiuShen. All Rights Reserved.

#include "ZipReader.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#ifdef WEBVIEW_CEF
#include "CefZipReader.h"
#endif
#include "cefcorelib.h"
bool UZipReader::Open(const FString& zipFile, const FString& passwd) {
#ifdef WEBVIEW_CEF
	zipFilePtr = MakeShared<UZipReaderImp>();
	return zipFilePtr->Open(zipFile, passwd);
#else
	return false;
#endif
}

bool UZipReader::IsValid() {
#ifdef WEBVIEW_CEF
	if (!zipFilePtr.IsValid())
		return zipFilePtr->IsValid();
#endif
	return false;
}

bool UZipReader::MoveToFirstFile() {
	if (!IsValid())return false;
#ifdef WEBVIEW_CEF
	return zipFilePtr->MoveToFirstFile();
#else
	return false;
#endif
}

bool UZipReader::MoveToNextFile() {
	if (!IsValid())return false;
#ifdef WEBVIEW_CEF
	return zipFilePtr->MoveToNextFile();
#else
	return false;
#endif
}

TArray<FString> UZipReader::GetAllFileNames() {
	if (!IsValid())return TArray<FString>();
#ifdef WEBVIEW_CEF
	return zipFilePtr->GetAllFileNames();
#else
	return TArray<FString>();
#endif
}


bool UZipReader::MoveToFile(const FString& _fileName, bool caseSensitive) {
	if (!IsValid())return false;
#ifdef WEBVIEW_CEF
	return zipFilePtr->MoveToFile(_fileName, caseSensitive);
#else
	return false;
#endif
}

FString UZipReader::GetFileName() {
	if (!IsValid())return FString();
#ifdef WEBVIEW_CEF
	return zipFilePtr->GetFileName();
#else
	return FString();
#endif
}

int32 UZipReader::GetFileSize() {
	if (!IsValid())return 0;
#ifdef WEBVIEW_CEF
	return zipFilePtr->GetFileSize();
#else
	return 0;
#endif
}

bool UZipReader::ReadToString(FString& data) {
	if (!IsValid())return false;
#ifdef WEBVIEW_CEF
	return zipFilePtr->ReadToString(data);
#else
	return false;
#endif
}

bool UZipReader::ReadToDir(const FString& Dir) {
	if (!IsValid())return false;
#ifdef WEBVIEW_CEF
	return zipFilePtr->ReadToDir(Dir);
#else
	return false;
#endif
}


bool UZipReader::ReadAllToDir(const FString& Dir) {
	if (!IsValid())return false;
#ifdef WEBVIEW_CEF
	return zipFilePtr->ReadAllToDir(Dir);
#else
	return false;
#endif
}
