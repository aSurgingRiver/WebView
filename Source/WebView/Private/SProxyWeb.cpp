// Copyright aXiuShen. All Rights Reserved.

#include "SProxyWeb.h"
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
#include "RenderingThread.h"
#include "Textures/SlateUpdatableTexture.h"
#include "Framework/Application/SlateApplication.h"
#include "Async/Async.h"
#ifdef USING_WEBBROWSER
#include "Misc/ConfigCacheIni.h"
#include "WebBrowserViewport.h"
#include "WebBrowserModule.h"
#include "IWebBrowserWindow.h"
#include "SWebBrowserView.h"

//#if WITH_EDITOR
//#include "Materials/MaterialInterface.h"
//#include "Materials/MaterialExpressionMaterialFunctionCall.h"
//#include "Materials/MaterialExpressionTextureSample.h"
//#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
//#include "Materials/MaterialFunction.h"
//#include "Materials/Material.h"
//#include "Factories/MaterialFactoryNew.h"
////#include "AssetRegistryModule.h"
//#include "PackageHelperFunctions.h"
//#endif

#define LOCTEXT_NAMESPACE "ProxyWeb"

SProxyWeb::SProxyWeb()
	: local_dns(TEXT("local:/"))
{
	SetCanTick(true);
	bMouseTransparency = false;
	TransparencyThreadshold = 255;
	GConfig->GetString(TEXT("WebView"), TEXT("local_domain"), local_domain, GGameIni);
	if (!local_domain.IsEmpty()) {
		FString con = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
		local_domain = FPaths::Combine(*con,*local_domain);
	}
}

SProxyWeb::~SProxyWeb() {
	
}

FString SProxyWeb::dns_to_local(FString url)const {
	if (local_domain.IsEmpty()||!url.StartsWith(local_dns)) return url;
	return url.Replace(*local_dns, *local_domain);
}

FString SProxyWeb::local_to_dns(FString url) const {
	if (local_domain.IsEmpty() || !url.StartsWith(local_domain)) return url;
	return url.Replace(*local_domain, *local_dns);
}

void SProxyWeb::Construct(const FArguments& InArgs){

	IWebBrowserSingleton* Singleton = IWebBrowserModule::Get().GetSingleton();
	if (Singleton) {
		FCreateBrowserWindowSettings Settings;
		Settings.BrowserFrameRate = FMath::Clamp(InArgs._BrowserFrameRate, 30, 60);
		Settings.bUseTransparency = InArgs._EnableMouseTransparency;
		Settings.BackgroundColor = InArgs._BackgroundColor;
		Settings.InitialURL = dns_to_local(InArgs._InitialURL);
		Settings.ContentsToLoad = FString(TEXT(""));
		Settings.bShowErrorMessage = false;
		Settings.bThumbMouseButtonNavigation = false;
		Singleton->SetDevToolsShortcutEnabled(Settings.bShowErrorMessage);
		BrowserWindow = Singleton->CreateBrowserWindow(Settings);
	}
#ifdef WEBVIEW_CUSTOMIZED_CORE
	FString show_tips = TEXT("If you see this prompt, it is caused by the following reasons: \n\n"
		"1. The plug - in is installed in the engine directory, such as : Engine\\Plugins\\Marketplace. \n"
		"   Solution: Please move the plug - in to the project local plug - in directory \n\n"
		"2. Other plug - ins that depend on WebBrowser are enabled, such as : Bridge, WebBrowser, etc. \n"
		"   Solution : Disable them in the plug - in manager. \n\n"
		"Finally, close the project and then open it again.\n");
	TAttribute<FText> text_tip = FText::FromString(show_tips);
	TSharedRef<STextBlock> TextRef = SNew(STextBlock);
	TextRef->SetText(text_tip);
	TextRef->SetTextStyle(&InArgs._TextStyle);
#endif
	bMouseTransparency = InArgs._EnableMouseTransparency;
	TransparencyThreadshold = 255 - InArgs._BackgroundColor.A;
	LastMousePixel = FColor::Transparent;
	ChildSlot
	[
		SNew(SOverlay)
		.Visibility(this, &SProxyWeb::GetViewportVisibility)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill).VAlign(VAlign_Fill)
		[
			SAssignNew(BrowserView, SWebBrowserView, BrowserWindow)
			.InitialURL(dns_to_local(InArgs._InitialURL))
			.ShowErrorMessage(false)
			.SupportsTransparency(true)
			.SupportsThumbMouseButtonNavigation(false)
			.BackgroundColor(InArgs._BackgroundColor)
			.ViewportSize(InArgs._ViewportSize)
			.OnUrlChanged(InArgs._OnUrlChanged)
			.OnBeforePopup(InArgs._OnBeforePopup)
		]
#ifdef WEBVIEW_CUSTOMIZED_CORE
		+ SOverlay::Slot()
			.HAlign(HAlign_Center).VAlign(VAlign_Center)
			[
				TextRef
			]
#endif
	];
}

EVisibility SProxyWeb::GetViewportVisibility() const {
	if (!BrowserView.IsValid() || !BrowserView->IsInitialized()) {
		return EVisibility::Hidden;
	}
	else if (bMouseTransparency && LastMousePixel.A < TransparencyThreadshold) {
		return EVisibility::HitTestInvisible;
	}
	return EVisibility::Visible;
}

void SProxyWeb::LoadURL(FString NewURL, FString PostData , bool need_response ) {
	if (BrowserView.IsValid())
		BrowserView->LoadURL(dns_to_local(NewURL));
}
void SProxyWeb::LoadString(FString NewURL, FString content) {
	if (BrowserView.IsValid())
		BrowserView->LoadString(content, dns_to_local(NewURL));
}

void SProxyWeb::ReopenRender(FString NewURL) {
	LoadURL(dns_to_local(NewURL));//don`t support open new render. use loadurl impl
}

void SProxyWeb::Reload() {
	if (BrowserView.IsValid())
		BrowserView->Reload();
}

void SProxyWeb::StopLoad(){
	if (BrowserView.IsValid())
		BrowserView->StopLoad();
}

FText SProxyWeb::GetTitleText() const {
	if (BrowserView.IsValid())
		return BrowserView->GetTitleText();
	return FText();
}

FString SProxyWeb::GetUrl() const
{
	if (BrowserView.IsValid())
		return local_to_dns(BrowserView->GetUrl());
	return FString();
}

bool SProxyWeb::IsLoading() const
{
	if (BrowserView.IsValid())
		return BrowserView->IsLoading();
	return false;
}

bool SProxyWeb::CanGoBack() const
{
	if (BrowserView.IsValid())
		return BrowserView->CanGoBack();
	return false;
}

void SProxyWeb::GoBack()
{
	if (BrowserView.IsValid())
		BrowserView->GoBack();
}

bool SProxyWeb::CanGoForward() const {
	if (BrowserView.IsValid())
		return BrowserView->CanGoForward();
	return false;
}

void SProxyWeb::GoForward() {
	if (BrowserView.IsValid())
		BrowserView->GoForward();
}

void SProxyWeb::ZoomLevel(float zoomlevel) {
	// do not implment
}

void SProxyWeb::WebPixel(FIntPoint pixel) {
	// do not implment
}

void SProxyWeb::ExecuteJavascript(const FString& ScriptText){
	if (BrowserView.IsValid())
		BrowserView->ExecuteJavascript(ScriptText);
}

void SProxyWeb::BindUObject(const FString& Name, UObject* Object, bool bIsPermanent){
	if (BrowserView.IsValid())
		BrowserView->BindUObject(Name, Object, bIsPermanent);
}

void SProxyWeb::UnbindUObject(const FString& Name, UObject* Object, bool bIsPermanent){
	if (BrowserView.IsValid())
		BrowserView->UnbindUObject(Name, Object, bIsPermanent);
}

void SProxyWeb::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) {
	if (!bMouseTransparency || !FSlateApplication::IsInitialized()) {//
		this->LastMousePixel = FColor::White;
		return;
	}
	sumDelay += InDeltaTime;
	if (sumDelay < 0.2f) return;
	sumDelay = 0.0f;

	TSharedPtr<ICursor> Mouse = FSlateApplication::Get().GetPlatformCursor();
	if (!Mouse.IsValid() /*|| Mouse->GetType() == EMouseCursor::None*/) {
		LastMousePixel = FColor::Transparent;
		return;
	}
	FVector2D MousePosition = Mouse->GetPosition();
	if (MousePosition.ContainsNaN()) {
		LastMousePixel = FColor::Transparent;
		return;
	}
	FVector2D LocalMouse = AllottedGeometry.AbsoluteToLocal(MousePosition);
	FVector2D LocalSize = AllottedGeometry.GetLocalSize();
	int X = LocalMouse.X * 1000;
	int Y = LocalMouse.Y * 1000;
	if (preMouseX == X && preMouseY == Y) {
		//UE_LOG(CoreWebLog, Log, TEXT("UWebCoreData::Tick no move %f %s"), LastMousePixel.A, *BrowserWindow->GetTitle());
		return;// 
	}
	preMouseX = X;
	preMouseY = Y;
	FVector2D LocalUV;
	if (LocalSize.X > 0.0f && LocalSize.Y > 0.0f)
		LocalUV = FVector2D(LocalMouse.X / LocalSize.X, LocalMouse.Y / LocalSize.Y);

	if (LocalUV.X >= 0.0f && LocalUV.X <= 1.0f && LocalUV.Y >= 0.0f && LocalUV.Y <= 1.0f) {
		ReadTexturePixel(LocalUV, LastMousePixel);
		return;
	}
	LastMousePixel = FColor::White;
	return;
}

bool SProxyWeb::ReadTexturePixel(FVector2D& LocalUV, FColor& MousePixel) {
	MousePixel = FColor::Transparent;
	if (!BrowserWindow.IsValid())
		return false;

	FSlateShaderResource* Resource = BrowserWindow->GetTexture();
	if (!Resource || Resource->GetType() != ESlateShaderResource::NativeTexture)
		return false;

	int width = Resource->GetWidth();
	int height = Resource->GetHeight();

	int X = FMath::FloorToInt(LocalUV.X * width);
	int Y = FMath::FloorToInt(LocalUV.Y * height);
	if (X < 0 || width < X || Y < 0 || height < Y) {
		MousePixel = FColor::Transparent;
		return false;
	}

	FTexture2DRHIRef TextureRHI;
	TextureRHI = ((TSlateTexture<FTexture2DRHIRef>*)Resource)->GetTypedResource();
	struct FReadSurfaceContext {
		FTexture2DRHIRef Texture;
		TArray<FColor>* OutData;
		FIntRect Rect;
		FReadSurfaceDataFlags Flags;
	};

	X = FMath::Clamp(X, 0, width - 1);
	Y = FMath::Clamp(Y, 0, height - 1);
	int Width = 1;
	int Height = 1;
	Width = FMath::Clamp(Width, 1, width);
	Width = Width - FMath::Max(X + Width - width, 0);

	Height = FMath::Clamp(Height, 1, height);
	Height = Height - FMath::Max(Y + Height - height, 0);
	TArray<FColor> OutPixels;
	FReadSurfaceContext Context =
	{
		TextureRHI,
		&OutPixels,
		FIntRect(X, Y, X + Width, Y + Height),
		FReadSurfaceDataFlags()
	};
	ENQUEUE_RENDER_COMMAND(ReadSurfaceCommand)(
		[Context, &MousePixel](FRHICommandListImmediate& RHICmdList)
		{
			TArray<FColor> OutPixels;
			RHICmdList.ReadSurfaceData(
				Context.Texture,
				Context.Rect,
				OutPixels,
				Context.Flags
			);
			if (OutPixels.Num())
				AsyncTask(ENamedThreads::Type::GameThread, [&MousePixel, Pixel = OutPixels[0]]() {MousePixel = Pixel; });
		});
	return true;
}

void SProxyWeb::OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) {
	// do not implment
}
void SProxyWeb::OnDragLeave(const FDragDropEvent& DragDropEvent) {
	// do not implment
}
FReply SProxyWeb::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) {
	// do not implment
	return FReply::Unhandled();
}

FReply SProxyWeb::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) {
	// do not implment
	return FReply::Unhandled();
}

void SProxyWeb::ShowAddress(bool isShow) {
	// do not implment
}

#undef LOCTEXT_NAMESPACE

#endif