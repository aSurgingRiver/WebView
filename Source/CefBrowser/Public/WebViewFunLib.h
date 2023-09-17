// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WebCookie.h"
#include "ZipReader.h"
#include "WebViewFunLib.generated.h"

/**
 * 
 */
UCLASS()
class CEFBROWSER_API UWebViewFunLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Set web cookie
	*/
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static bool SetCookie(const FString& URL, const FWebCookie& Cookie);
	/**
	* delete web cookie
	*/
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static bool DeleteCookies(const FString& URL, const FString& CookieName);
	/**
	* encode url to %%%%
	* @param URL : 
	* @param use_plus : is true spaces will change to "+".
	*/
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static FString EncodeURL(const FString& URL,const bool use_plus=false);

	/**
	* open external browser
	* @param URL
	*/
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static void PopupURL(const FString& URL);


	/**
	 * convert data to base64 string
	 * @param data To be encoded
	 * @return Encoding result data
	 */
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static FString Base64Encode(const FString& data);

	/**
	 * Decoding encoded base64 string
	 * @param base64 Data to be decoded
	 * @return Decoding result data
	*/
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static FString Base64Decode(const FString& base64);

	/**
	 * convert file content to base64 string
	 * @param file To be encoded
	 * @return Encoding result data
	*/
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static FString Base64EncodeFile(const FString& file );

	/**
	 * Decoding encoded base64 string into file
	 * @param base64 Data to be decoded
	 * @param SaveFile use to save Decoding result data
	 * @return false is failed,true is successful
	*/
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static bool Base64DecodeFile(const FString& base64, const FString& SaveFile);

	/**
	 * Compress the directory into a zip file
	 * @param Dir Directory to be compressed
	 * @param ZipFile Save compressed file name
	 * @param IncludeHiddenFiles true Compress hidden files
	 * @return false is failed,true is successful
	 */
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static bool Zip(const FString& Dir, const FString& ZipFile, const bool IncludeHiddenFiles);

	/**
	 * Open compressed file
	 * @param zipFile compressed file name
	 * @param passwd Compress password
	 * @param Reader Compress Objects
	 * @return false is failed,true is successful
	 */
	UFUNCTION(BlueprintCallable, Category = "Web View")
	static bool UnZip(const FString& zipFile, const FString& passwd, UZipReader*& Reader);

};
