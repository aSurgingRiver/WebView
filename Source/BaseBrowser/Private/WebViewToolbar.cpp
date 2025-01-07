// Copyright Epic Games, Inc. All Rights Reserved.

#include "WebViewToolbar.h"
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

#define LOCTEXT_NAMESPACE "WebViewToolbar"

SWebViewToolbar::SWebViewToolbar()
{ 
}

SWebViewToolbar::~SWebViewToolbar()
{
	WebViewWindow = nullptr;
}

void SWebViewToolbar::IsAddress(bool v) {
	isAddress = v;
	isShow = isShow || isAddress;
}

void SWebViewToolbar::Construct(const FArguments& InArgs, TSharedPtr<IWebViewWindow, ESPMode::ThreadSafe> InWebViewWindow)
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
					.Text(this, &SWebViewToolbar::GetControlText)
					.TextStyle(&InArgs._TextStyle)
					.OnClicked(this, &SWebViewToolbar::OnShowClicked)
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SHorizontalBox)
				.Visibility(this, &SWebViewToolbar::ControlShow)
				//.Visibility(InArgs._ShowControls ? EVisibility::Visible : EVisibility::Collapsed)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("Back", "Back"))
					.TextStyle(&InArgs._TextStyle)
					.IsEnabled(this, &SWebViewToolbar::CanGoBack)
					.OnClicked_Raw(this, &SWebViewToolbar::OnBackClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("Forward", "Forward"))
					.TextStyle(&InArgs._TextStyle)
					.IsEnabled(this, &SWebViewToolbar::CanGoForward)
					.OnClicked(this, &SWebViewToolbar::OnForwardClicked)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(this, &SWebViewToolbar::GetReloadButtonText)
					.TextStyle(&InArgs._TextStyle)
					.OnClicked(this, &SWebViewToolbar::OnReloadClicked)
				]
			]
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Fill)
			.Padding(5.f, 5.f)
			[
				// @todo: A proper addressbar widget should go here, for now we use a simple textbox.
				SNew(SEditableTextBox)
				.Visibility(this, &SWebViewToolbar::AddressShow)
				.OnTextCommitted(this, &SWebViewToolbar::OnUrlTextCommitted)
				.Text_Lambda([this]() {return WebViewWindow.IsValid()?FText::FromString(WebViewWindow->GetUrl()): LOCTEXT("", ""); })
				.Font(InArgs._TextStyle.Font)
				.SelectAllTextWhenFocused(true)
				.ClearKeyboardFocusOnCommit(true)
				.RevertTextOnEscape(true)
			]
		]
	];
}

FText   SWebViewToolbar::GetControlText() const {
	return isShow ? LOCTEXT("<", "<") : LOCTEXT(">", ">");
}

EVisibility SWebViewToolbar::ControlShow() const {
	return isShow && isControl ? EVisibility::Visible : EVisibility::Collapsed;
}

EVisibility SWebViewToolbar::AddressShow() const {
	return (isAddress && isShow) ? EVisibility::Visible : EVisibility::Collapsed;
}

FText SWebViewToolbar::GetTitleText() const {
	FText ret;
	if (WebViewWindow.IsValid()) {
		ret = FText::FromString(WebViewWindow->GetTitle());
	}
	return ret;
}

FString SWebViewToolbar::GetUrl() const
{
	if (WebViewWindow.IsValid()) {
		return WebViewWindow->GetUrl();
	}
	return FString();
}

bool SWebViewToolbar::IsLoading() const
{
	if (WebViewWindow.IsValid()) {
		return WebViewWindow->IsLoading();
	}
	return false;
}

bool SWebViewToolbar::CanGoBack() const
{
	if (WebViewWindow.IsValid()) {
		return WebViewWindow->CanGoBack();
	}
	return false;
}

void SWebViewToolbar::GoBack()
{
	if (WebViewWindow.IsValid()) {
		WebViewWindow->GoBack();
	}
}

FReply SWebViewToolbar::OnShowClicked() {
	isShow = !isShow;
	return FReply::Handled();
}

FReply SWebViewToolbar::OnBackClicked()
{
	if (WebViewWindow.IsValid()) {
		WebViewWindow->GoBack();
		return FReply::Handled();
	}
	return FReply::Unhandled();
}

bool SWebViewToolbar::CanGoForward() const {
	if (WebViewWindow.IsValid()) {
		return WebViewWindow->CanGoForward();
	}
	return false;
}

void SWebViewToolbar::GoForward() {
	if (WebViewWindow.IsValid()) {
		WebViewWindow->GoForward();
	}
}


FText SWebViewToolbar::GetReloadButtonText() const
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

FReply SWebViewToolbar::OnReloadClicked()
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

void SWebViewToolbar::OnUrlTextCommitted(const FText& NewText, ETextCommit::Type CommitType)
{
	if (CommitType == ETextCommit::OnEnter && WebViewWindow.IsValid()) {
		WebViewWindow->LoadURL(NewText.ToString(),FString(),false);
	}
}

FReply SWebViewToolbar::OnForwardClicked()
{
	if (!WebViewWindow.IsValid())return FReply::Unhandled();
	WebViewWindow->GoForward();
	return FReply::Handled();
}
#undef LOCTEXT_NAMESPACE
