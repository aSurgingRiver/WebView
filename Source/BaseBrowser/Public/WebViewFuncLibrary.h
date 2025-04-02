// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WebViewFuncLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BASEBROWSER_API UWebViewFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static FString OpenDirectoryDialog(FString title , FString default_path);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	static TArray<FString> OpenFilesDialog(FString title, FString default_path);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	static FString OpenFileDialog(FString title, FString default_path);

	UFUNCTION(BlueprintCallable, Category = "Web View")
	static FString SaveFileDialog(FString title, FString default_path);

//virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;
//virtual bool OpenFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames, int32& OutFilterIndex) override;
//virtual bool SaveFileDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, const FString& DefaultFile, const FString& FileTypes, uint32 Flags, TArray<FString>& OutFilenames) override;
//virtual bool OpenDirectoryDialog(const void* ParentWindowHandle, const FString& DialogTitle, const FString& DefaultPath, FString& OutFolderName) override;

};
