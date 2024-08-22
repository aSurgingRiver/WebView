// Copyright aXiuShen. All Rights Reserved.

#include "ZipReader.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#ifndef USING_WEBBROWSER
#include "CefZipReader.h"
#endif
#include "cefcorelib.h"
bool UZipReader::Open(const FString& zipFile, const FString& passwd) {
#ifndef USING_WEBBROWSER
	zipFilePtr = MakeShared<UZipReaderImp>();
	return zipFilePtr->Open(zipFile, passwd);
#else
	return false;
#endif
}

bool UZipReader::IsValid() {
#ifndef USING_WEBBROWSER
	if (!zipFilePtr.IsValid())
		return zipFilePtr->IsValid();
#endif
	return false;
}

bool UZipReader::MoveToFirstFile() {
	if (!IsValid())return false;
#ifndef USING_WEBBROWSER
	return zipFilePtr->MoveToFirstFile();
#else
	return false;
#endif
}

bool UZipReader::MoveToNextFile() {
	if (!IsValid())return false;
#ifndef USING_WEBBROWSER
	return zipFilePtr->MoveToNextFile();
#else
	return false;
#endif
}

TArray<FString> UZipReader::GetAllFileNames() {
	if (!IsValid())return TArray<FString>();
#ifndef USING_WEBBROWSER
	return zipFilePtr->GetAllFileNames();
#else
	return TArray<FString>();
#endif
}


bool UZipReader::MoveToFile(const FString& _fileName, bool caseSensitive) {
	if (!IsValid())return false;
#ifndef USING_WEBBROWSER
	return zipFilePtr->MoveToFile(_fileName, caseSensitive);
#else
	return false;
#endif
}

FString UZipReader::GetFileName() {
	if (!IsValid())return FString();
#ifndef USING_WEBBROWSER
	return zipFilePtr->GetFileName();
#else
	return FString();
#endif
}

int32 UZipReader::GetFileSize() {
	if (!IsValid())return 0;
#ifndef USING_WEBBROWSER
	return zipFilePtr->GetFileSize();
#else
	return 0;
#endif
}

bool UZipReader::ReadToString(FString& data) {
	if (!IsValid())return false;
#ifndef USING_WEBBROWSER
	return zipFilePtr->ReadToString(data);
#else
	return false;
#endif
}

bool UZipReader::ReadToDir(const FString& Dir) {
	if (!IsValid())return false;
#ifndef USING_WEBBROWSER
	return zipFilePtr->ReadToDir(Dir);
#else
	return false;
#endif
}


bool UZipReader::ReadAllToDir(const FString& Dir) {
	if (!IsValid())return false;
#ifndef USING_WEBBROWSER
	return zipFilePtr->ReadAllToDir(Dir);
#else
	return false;
#endif
}
