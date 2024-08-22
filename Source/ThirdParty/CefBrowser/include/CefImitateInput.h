// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/SlateDelegates.h"
#include "warp_macro.h"


namespace cef {
	enum WebView_ImitateInput_Mouse
	{
		WebView_ImitateInput_Mouse_Down = 0,
		WebView_ImitateInput_Mouse_Up = 1,
		WebView_ImitateInput_Mouse_Move = 2,
	};

	enum WebView_ImitateInput_Key
	{
		WebView_ImitateInput_Key_Down = 0,
		WebView_ImitateInput_Key_Up = 1,
		WebView_ImitateInput_Key_Char = 2,
	};


	struct FImitateInput 
	{
	public:

		/*
		 * Show web content when Imitate Input
		 */
		bool Show = true;

		/*
		 * Time interval between events .ms , If the interval time is insufficient, call the AddDelay node to increase
		 */
		int interval = 20;

		/*
		 * Simulate event screen resolution.  After setting, it can adapt to any resolution.
		 * Please keep the size and webpixel values the same in the editor
		 */
		FIntPoint Size = FIntPoint(0, 0);

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
		TArray<FString> Event;
	};

	enum class WebView_Keyboard_Mode : uint8
	{
		WebView_Keyboard_Mode_Scenes = 1,
		WebView_Keyboard_Mode_Blend = 0,
		WebView_Keyboard_Mode_Both = 2,
	};
}