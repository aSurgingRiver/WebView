// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#ifdef WEBVIEW_CUSTOMIZED_CORE
#include "CefImitateInput.h"
#endif
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/SlateDelegates.h"
#include "ImitateInput.generated.h"

UENUM(BlueprintType, Category = "Web View", meta = (DisplayName = "Imitate Input Mouse"))
enum class WebView_ImitateInput_Mouse : uint8
{
	WebView_ImitateInput_Mouse_Down = 0 UMETA(DisplayName = "MouseDown"),
	WebView_ImitateInput_Mouse_Up = 1 UMETA(DisplayName = "MouseUp"),
	WebView_ImitateInput_Mouse_Move = 2 UMETA(DisplayName = "MouseMove"),
};

UENUM(BlueprintType, Category = "Web View", meta = (DisplayName = "Imitate Input Key"))
enum class WebView_ImitateInput_Key : uint8
{
	WebView_ImitateInput_Key_Down = 0 UMETA(DisplayName = "KeyDown"),
	WebView_ImitateInput_Key_Up = 1 UMETA(DisplayName = "KeyUp"),
	WebView_ImitateInput_Key_Char = 2 UMETA(DisplayName = "KeyChar"),
};


USTRUCT(BlueprintType)
struct WEBVIEW_API FImitateInput //public UObject
{
public:
	GENERATED_USTRUCT_BODY()

	/*
	 * Show web content when Imitate Input
	 */ 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Web View")
	bool Show = true;

	/*
	 * Time interval between events .ms , If the interval time is insufficient, call the AddDelay node to increase
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 10, UIMax = 10000), Category = "Web View")
	int interval = 20;

	/*
	 * Simulate event screen resolution.  After setting, it can adapt to any resolution. 
	 * Please keep the size and webpixel values the same in the editor
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Web View")
	FIntPoint Size= FIntPoint(0, 0);

	/* 
	{"type":"delay","ms":3000}
	{"type":"input","text":"content"}
	{"type":"key_down","code":0,"character":0,"modify":0}
	{"type":"key_char","code":0,"character":0,"modify":0}
	{"type":"key_up","code":0,"character":0,"modify":0}
	{"type":"mouse_down","pos":{"x":128,"y":256}}
	{"type":"mouse_move","pos":{"x":128,"y":256}}
	{"type":"mouse_up","pos":{"x":128,"y":256}}
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Web View")
	TArray<FString> Event;
};




UENUM(BlueprintType, Category = "Web View")
enum class WebView_Keyboard_Mode: uint8
{
	WebView_Keyboard_Mode_Scenes = 1 UMETA(DisplayName = "Scenes"),
	WebView_Keyboard_Mode_Blend = 0 UMETA(DisplayName = "Blend"),
	WebView_Keyboard_Mode_Both = 2 UMETA(DisplayName = "Both"),
};
#ifdef WEBVIEW_CUSTOMIZED_CORE
namespace webview {
	cef::WebView_Keyboard_Mode toInner(WebView_Keyboard_Mode);
	cef::FImitateInput toInner(FImitateInput);
	cef::WebView_ImitateInput_Key toInner(WebView_ImitateInput_Key);
	cef::WebView_ImitateInput_Mouse toInner(WebView_ImitateInput_Mouse);
}
#endif