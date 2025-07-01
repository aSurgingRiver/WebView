// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once



//#ifdef WEBVIEW_CEF

#include "CoreMinimal.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/PopupMethodReply.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/Application/IMenu.h"
#include "Framework/SlateDelegates.h"
#include "Widgets/SViewport.h"
#include "Internationalization/Text.h"
#include "ImitateInput.h"
#include "WebViewEnum.h"

class IWebCoreAdapter;
class IWebCoreDialog;
class IWebCorePopupFeatures;
class IWebViewWindow;


//typedef SViewport SWebCoreWidget;

class BASEBROWSER_API SWebViewToolbar
	: public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SWebViewToolbar)
	{ 
		_Visibility = EVisibility::SelfHitTestInvisible;
	}

		/** Whether to show standard controls like Back, Forward, Reload etc. */
		SLATE_ARGUMENT(bool, ShowControls)

		/** Whether to show an address bar. */
		SLATE_ARGUMENT(bool, ShowAddressBar)

		SLATE_ARGUMENT(FTextBlockStyle, TextStyle)
	SLATE_END_ARGS()

	/** Default constructor. */
	SWebViewToolbar();

	~SWebViewToolbar();

	virtual bool SupportsKeyboardFocus() const override {return true;}

	/**
	 * Construct the widget.
	 *
	 * @param InArgs  Declaration from which to construct the widget.
	 */
	void Construct(const FArguments& InArgs, TSharedPtr<IWebViewWindow,ESPMode::ThreadSafe> InWebCoreWindow);

	void IsAddress(bool v);
private:
	//void   LoadTimeout();
	FReply OnShowClicked();
	FReply OnBackClicked();
	FReply OnForwardClicked();
	FText   GetTitleText() const;
	FText   GetControlText() const;
	EVisibility ControlShow() const;
	EVisibility AddressShow() const;
	FString GetUrl() const;
	bool    IsLoading() const;
	bool    CanGoBack() const;
	void    GoBack();
	bool    CanGoForward() const;
	void    GoForward();
	FText   GetReloadButtonText()const;
	FReply  OnReloadClicked();
	FReply  OnGo();
	void    OnTextChanged(const FText& NewText, ETextCommit::Type CommitType);
	void    OnUrlTextCommitted(const FText& NewText, ETextCommit::Type CommitType);
	void    OnTextChanged(const FText& InText);


private:
	FText        ChangeText;
	bool         isShow;
	bool         isAddress;
	bool         isControl;
protected:
	/** Interface for dealing with a web browser window. */
	TSharedPtr<IWebViewWindow,ESPMode::ThreadSafe> WebViewWindow;
};


//#endif