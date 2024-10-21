// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "cef_export_macro.h"


namespace webview {
	struct _ZIPFILES;
}
	class CEFBROWSER_DLL UZipReaderImp
	{
	public:
		/**
		 * Open on zip file
		 * @param zipFile only support zip
		 * @param passwd pass word
		 * @return false is failed,true is successful and move to first file
		 */
		bool Open(const FString& zipFile, const FString& passwd);
		/**
		 * Get zip all file list. contains dir
		 * @return all file
		 *         e.g: file1.txt dir/ dir/file.png
		 */
		TArray<FString> GetAllFileNames();
		/**
		 * move pointer of file to first
		 * @return false is failed,true is successful
		 */
		bool MoveToFirstFile();
		/**
		 * move pointer of file to next from cur position
		 * @return false is failed,true is successful
		 */
		bool MoveToNextFile();
		/**
		 * move pointer of file to special file
		 * @param fileName Move to destination file location
		 * @param caseSensitive Match case
		 * @return false is failed,true is successful
		 */
		bool MoveToFile(const FString& fileName, bool caseSensitive = true);
		/**
		 * Get the current file name
		 * @return file name
		 */
		FString GetFileName();
		/**
		 * Get the current file size
		 * @return file size
		 */
		int32 GetFileSize();
		/**
		 * Get the current file content into buffer
		 * @param data file content
		 * @return false is failed,true is successful
		 */
		bool ReadToString(FString& data);
		/**
		 * Get the current file content into directory
		 * @param Dir directory used to save file
		 * @return false is failed,true is successful
		 */
		bool ReadToDir(const FString& Dir);
		/**
		 * Get all files content into directory
		 * @param Dir directory used to save file
		 * @return false is failed,true is successful
		 */
		bool ReadAllToDir(const FString& Dir);
		/**
		 * check object has open zip file
		 * @return false is failed,true is successful
		 */
		bool IsValid();
	private:

	private:
		TSharedPtr<webview::_ZIPFILES> zipFilePtr;
	};