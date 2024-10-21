// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WebCookie.h"
#include "ZipReader.h"
#include "ImitateInput.h"
#include "WebViewFunLib.generated.h"

/**
 * 
 */
UCLASS()
class WEBVIEW_API UWebViewFunLib : public UBlueprintFunctionLibrary
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





	/**
	 * Add Mouse Event
	 * @param mouse : Mouse Event Type
	 * @param point : Screen coordinates for mouse event input
	 */
	UFUNCTION(BlueprintCallable, Category = "Web View")
		static	FImitateInput& AddMouse(UPARAM(ref) FImitateInput& screen,const WebView_ImitateInput_Mouse mouse, const FIntPoint& point);

	/**
	 * Add mouse click event
	 * @param point : Screen coordinates for mouse event input
	 * @note : Including mouse press and release
	 */
	UFUNCTION(BlueprintCallable, Category = "Web View")
		static	FImitateInput& AddClicked(UPARAM(ref) FImitateInput& screen, const FIntPoint& point);

	/**
	 * Enter text
	 */
	UFUNCTION(BlueprintCallable, Category = "Web View")
		static	FImitateInput& AddText(UPARAM(ref) FImitateInput& screen, const FString& text);
	
	/**
	 * Add delay between events
	 */
	UFUNCTION(BlueprintCallable, Category = "Web View")
		static	FImitateInput& AddDelay(UPARAM(ref) FImitateInput& screen, const int ms);

	UFUNCTION(BlueprintCallable, Category = "Web View")
		static	FImitateInput& AddKeystroke(UPARAM(ref) FImitateInput& screen, const WebView_ImitateInput_Key keyboard, const FKey& key, const TArray<FKey>& CombinKey);

	/**
	 * Analog keyboard input, 
	 * @param key : To input button
	 * @param CombinKey : Combination keys such as shift, ctrl, alt, etc 
	 */
	UFUNCTION(BlueprintCallable, Category = "Web View")
		static FImitateInput& AddKey(UPARAM(ref) FImitateInput& screen, const FKey& key, const TArray<FKey> CombinKey);

	/**
	* show mouse event position, default off
	*/
	UFUNCTION(BlueprintCallable, Category = "Web View")
		static	FImitateInput& ShowLog(UPARAM(ref) FImitateInput& screen, bool on = false);
	
	/**
	* clear all event info
	*/
	UFUNCTION(BlueprintCallable, Category = "Web View")
		static FImitateInput& Clear(UPARAM(ref) FImitateInput& screen);
};
