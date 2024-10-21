// Copyright aXiuShen. All Rights Reserved.
#include "IWebViewWindow.h"

IWebViewWindow::~IWebViewWindow() {
}
IWebViewWindow::IWebViewWindow() {
}


webview::FOnWebState& IWebViewWindow::OnWebState() {
	return _OnWebState;
}
webview::FOnTitleChanged& IWebViewWindow::OnTitleChanged(){
	return _OnTitleChanged;
}
webview::FOnUrlChanged& IWebViewWindow::OnUrlChanged(){
	return _OnUrlChanged;
}
webview::FOnChkTrans& IWebViewWindow::OnChkTrans(){
	return _OnChkTrans;
}
webview::FOnBeforePopupDelegate& IWebViewWindow::OnBeforePopup(){
	return _OnBeforePopup;
}
webview::FOnDownloadComplete& IWebViewWindow::OnDownloadComplete(){
	return _OnDownloadComplete;
}
webview::FOnPostResponse& IWebViewWindow::OnPostResponse(){
	return _OnPostResponse;
}
webview::FOnDragEvent& IWebViewWindow::OnDragEvent(){
	return _OnDragEvent;
}
webview::FOnRenderCrash& IWebViewWindow::OnRenderCrash(){
	return _OnRenderCrash;
}
webview::FOnResourceLoad& IWebViewWindow::OnResourceLoad(){
	return _OnResourceLoad;
}
webview::FOnNeedsRedraw& IWebViewWindow::OnNeedsRedraw(){
	return _OnNeedsRedraw;
}
webview::FOnJsStr& IWebViewWindow::OnJsStr(){
	return _OnJsStr;
}
webview::FOnJs& IWebViewWindow::OnJs(){
	return _OnJs;
}
webview::FOnWebError& IWebViewWindow::OnWebError(){
	return _OnWebError;
}


FReply IWebViewWindow::OnTouchMoved(const FGeometry& , const FPointerEvent& ) {
	return FReply::Unhandled();
}

FReply IWebViewWindow::OnTouchStarted(const FGeometry& , const FPointerEvent& ) {
	return FReply::Unhandled();
}

FReply IWebViewWindow::OnTouchEnded(const FGeometry& , const FPointerEvent& ) {
	return FReply::Unhandled();
}

FCursorReply IWebViewWindow::OnCursorQuery(const FGeometry& , const FPointerEvent& ) {
	return FCursorReply::Unhandled();
}


bool IWebViewWindow::IsLoading() const {
	return false;
}
bool IWebViewWindow::Isloaded()  {
	return false;
}
void IWebViewWindow::OnDragEnter(const FGeometry& , const FDragDropEvent& ) {}
void IWebViewWindow::OnDragLeave(const FDragDropEvent& ) {}
FReply IWebViewWindow::OnDragOver(const FGeometry& , const FDragDropEvent& ) {
	return FReply::Unhandled();
}
FReply IWebViewWindow::OnDrop(const FGeometry& , const FDragDropEvent& ) {
	return FReply::Unhandled();
}
void IWebViewWindow::StopRender(bool ) {
}
void IWebViewWindow::ShowDevTools() {}
void IWebViewWindow::Silent(bool onoff) {}
void IWebViewWindow::Rate(int r) {}