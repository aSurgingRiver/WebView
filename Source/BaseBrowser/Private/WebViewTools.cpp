// Copyright Epic Games, Inc. All Rights Reserved.


//#ifdef WEBVIEW_CEF

#include "WebViewTools.h"
#include "Misc/CommandLine.h"
#include "Misc/ConfigCacheIni.h"
#include "Containers/Ticker.h"
#include "Layout/WidgetPath.h"
#include "Framework/Application/MenuStack.h"
#include "Framework/Application/SlateApplication.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerInput.h"
#include "TimerManager.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "IWebViewWindow.h"

#define LOCTEXT_NAMESPACE "WebViewTools"

SWebViewTools::SWebViewTools()
{ 
}

SWebViewTools::~SWebViewTools()
{
	WebViewWindow = nullptr;
}

void SWebViewTools::IsAddress(bool v) {
	isAddress = v;
	isShow = isShow || isAddress;
}

void SWebViewTools::Construct(const FArguments& InArgs, TSharedPtr<IWebViewWindow, ESPMode::ThreadSafe> InWebViewWindow)
{
	WebViewWindow = InWebViewWindow; 
	if (!WebViewWindow.IsValid()) return;
	isAddress = InArgs._ShowAddressBar;
	isControl = InArgs._ShowControls;
	isShow = isAddress || isControl;
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Top)
		[
			SNew(SHorizontalBox)
			.Visibility((isShow) ? EVisibility::SelfHitTestInvisible : EVisibility::Collapsed)
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SHorizontalBox)
				.Visibility((isShow) ? EVisibility::Visible : EVisibility::Collapsed)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(this, &SWebViewTools::GetControlText)
					.TextStyle(&InArgs._TextStyle)
					.OnClicked(this, &SWebViewTools::OnShowClicked)
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SHorizontalBox)
				.Visibility(this, &SWebViewTools::ControlShow)
				//.Visibility(InArgs._ShowControls ? EVisibility::Visible : EVisibility::Collapsed)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("Back", "Back"))
					.TextStyle(&InArgs._TextStyle)
					.IsEnabled(this, &SWebViewTools::CanGoBack)
					.OnClicked_Raw(this, &SWebViewTools::OnBackClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("Forward", "Forward"))
					.TextStyle(&InArgs._TextStyle)
					.IsEnabled(this, &SWebViewTools::CanGoForward)
					.OnClicked(this, &SWebViewTools::OnForwardClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(this, &SWebViewTools::GetReloadButtonText)
					.TextStyle(&InArgs._TextStyle)
					.OnClicked(this, &SWebViewTools::OnReloadClicked)
				]
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Fill)
			.Padding(5.f, 5.f)
			[
				// @todo: A proper addressbar widget should go here, for now we use a simple textbox.
				SNew(SEditableTextBox)
				.Visibility(this, &SWebViewTools::AddressShow)
				.OnTextCommitted(this, &SWebViewTools::OnUrlTextCommitted)
				.Text_Lambda([this]() {return WebViewWindow.IsValid()?FText::FromString(WebViewWindow->GetUrl()): LOCTEXT("", ""); })
				.Font(InArgs._TextStyle.Font)
				.SelectAllTextWhenFocused(true)
				.ClearKeyboardFocusOnCommit(true)
				.RevertTextOnEscape(true)
			]
		]
	];
}

FText   SWebViewTools::GetControlText() const {
	return isShow ? LOCTEXT("<", "<") : LOCTEXT(">", ">");
}

EVisibility SWebViewTools::ControlShow() const {
	return isShow && isControl ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility SWebViewTools::AddressShow() const {
	return (isAddress && isShow) ? EVisibility::Visible : EVisibility::Collapsed;
}

FText SWebViewTools::GetTitleText() const {
	FText ret;
	if (WebViewWindow.IsValid()) {
		ret = FText::FromString(WebViewWindow->GetTitle());
	}
	return ret;
}

FString SWebViewTools::GetUrl() const
{
	if (WebViewWindow.IsValid()) {
		return WebViewWindow->GetUrl();
	}
	return FString();
}

bool SWebViewTools::IsLoading() const
{
	if (WebViewWindow.IsValid()) {
		return WebViewWindow->IsLoading();
	}
	return false;
}

bool SWebViewTools::CanGoBack() const
{
	if (WebViewWindow.IsValid()) {
		return WebViewWindow->CanGoBack();
	}
	return false;
}

void SWebViewTools::GoBack()
{
	if (WebViewWindow.IsValid()) {
		WebViewWindow->GoBack();
	}
}

FReply SWebViewTools::OnShowClicked() {
	isShow = !isShow;
	return FReply::Handled();
}

FReply SWebViewTools::OnBackClicked()
{
	if (WebViewWindow.IsValid()) {
		WebViewWindow->GoBack();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

bool SWebViewTools::CanGoForward() const {
	if (WebViewWindow.IsValid()) {
		return WebViewWindow->CanGoForward();
	}
	return false;
}

void SWebViewTools::GoForward() {
	if (WebViewWindow.IsValid()) {
		WebViewWindow->GoForward();
	}
}


FText SWebViewTools::GetReloadButtonText() const
{
	static FText ReloadText = LOCTEXT("Reload", "Reload");
	static FText StopText = LOCTEXT("StopText", "Stop");

	if (WebViewWindow.IsValid())
	{
		if (WebViewWindow->IsLoading()) {
			return StopText;
		}
	}
	return ReloadText;
}

FReply SWebViewTools::OnReloadClicked()
{
	if (!WebViewWindow.IsValid()) {
		return FReply::Handled();
	}
	if (IsLoading()) {
		WebViewWindow->StopLoad();
	}
	else {
		WebViewWindow->Reload();
	}
	return FReply::Handled();
}

void SWebViewTools::OnUrlTextCommitted(const FText& NewText, ETextCommit::Type CommitType)
{
	if (CommitType == ETextCommit::OnEnter && WebViewWindow.IsValid()) {
		WebViewWindow->LoadURL(NewText.ToString(),FString(),false);
	}
}

FReply SWebViewTools::OnForwardClicked()
{
	if (!WebViewWindow.IsValid())return FReply::Unhandled();
	WebViewWindow->GoForward();
	return FReply::Handled();
}
#undef LOCTEXT_NAMESPACE


//#endif