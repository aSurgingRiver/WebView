// Copyright aXiuShen. All Rights Reserved.

#include "ImitateInput.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Images/SThrobber.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define LOCTEXT_NAMESPACE "ImitateInput"

#ifdef WEBVIEW_CUSTOMIZED_CORE
namespace webview {
cef::WebView_Keyboard_Mode toInner(WebView_Keyboard_Mode k) {
	switch (k) {
	case WebView_Keyboard_Mode::WebView_Keyboard_Mode_Scenes: return cef::WebView_Keyboard_Mode::WebView_Keyboard_Mode_Scenes;
	case WebView_Keyboard_Mode::WebView_Keyboard_Mode_Blend: return cef::WebView_Keyboard_Mode::WebView_Keyboard_Mode_Blend;
	case WebView_Keyboard_Mode::WebView_Keyboard_Mode_Both: return cef::WebView_Keyboard_Mode::WebView_Keyboard_Mode_Both;
	}
	return cef::WebView_Keyboard_Mode::WebView_Keyboard_Mode_Both;
}
cef::FImitateInput toInner(FImitateInput in) {
	cef::FImitateInput out;
	out.Show = in.Show;
	out.interval = in.interval;
	out.Size = in.Size;
	out.Event = in.Event;
	return out;
}
cef::WebView_ImitateInput_Key toInner(WebView_ImitateInput_Key k) {
	switch (k) {
	case WebView_ImitateInput_Key::WebView_ImitateInput_Key_Down: return cef::WebView_ImitateInput_Key::WebView_ImitateInput_Key_Down;
	case WebView_ImitateInput_Key::WebView_ImitateInput_Key_Up: return cef::WebView_ImitateInput_Key::WebView_ImitateInput_Key_Up;
	case WebView_ImitateInput_Key::WebView_ImitateInput_Key_Char: return cef::WebView_ImitateInput_Key::WebView_ImitateInput_Key_Char;
	}
	return cef::WebView_ImitateInput_Key::WebView_ImitateInput_Key_Down;
}
cef::WebView_ImitateInput_Mouse toInner(WebView_ImitateInput_Mouse k) {
	switch (k) {
	case WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Down: return cef::WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Down;
	case WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Up: return cef::WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Up;
	case WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Move: return cef::WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Move;
	}
	return cef::WebView_ImitateInput_Mouse::WebView_ImitateInput_Mouse_Down;
}
}
#endif
#undef LOCTEXT_NAMESPACE
