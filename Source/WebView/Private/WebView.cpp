// Copyright aXiuShen. All Rights Reserved.

#include "WebView.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "Materials/Material.h"
#include "Widgets/Docking/SDockTab.h"
#include "SWebViewWidget.h"
#ifdef WEBVIEW_CEF
#include "WebModule.h"
#include "cef3lib.h"
#include "cefcorelib.h"
#endif
#if WITH_EDITOR
#include "Editor.h"
#include "WorkspaceMenuStructureModule.h"
#include "WorkspaceMenuStructure.h"
#include "Framework/Commands/Commands.h"
#include "LevelEditor.h"
#endif

#if WITH_EDITOR && 50700<=WEBVIEW_ENGINE_VERSION
//#include "IWebBrowserCookieManager.h"
#include "WebBrowserModule.h"
#endif

#define LOCTEXT_NAMESPACE "FWebViewModule"

static const FName WebViewTabName("WebView");
#if WITH_EDITOR && 50100<=WEBVIEW_ENGINE_VERSION
class FWebViewCommands : public TCommands<FWebViewCommands>
{
public:
	FWebViewCommands()
		: TCommands<FWebViewCommands>(
			TEXT("WebView"),
			NSLOCTEXT("Contexts", "WebView", "Web View"),
			NAME_None,
			FAppStyle::GetAppStyleSetName()
		)
	{
	}

	virtual void RegisterCommands() override {
		UI_COMMAND(
			OpenWebEditor,
			"Open Web View",
			"Open a new web view tab",
			EUserInterfaceActionType::Button,
			FInputChord()
		);
	}

public:
	TSharedPtr<FUICommandInfo> OpenWebEditor;
};
#endif

class FWebViewModule : public IWebViewModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
private:
#if WITH_EDITOR && 50100<=WEBVIEW_ENGINE_VERSION
	TSharedRef<SDockTab> SpawnWebViewTab(const FSpawnTabArgs& Args);
	void AddMenuEntry(FMenuBuilder& MenuBuilder);
	void OpeWebViewTab();
#endif
};

void FWebViewModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  
	// For modules that support dynamic reloading,
	// we call this function before unloading the module.
#if defined WEBVIEW_CEF && !defined USING_WEBBROWSER
	webview::IBrowserInstance::Get().UnLoad();
#endif
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner("WebViewTab");
}

void FWebViewModule::StartupModule()
{
#if WITH_EDITOR && 50700<=WEBVIEW_ENGINE_VERSION
	IWebBrowserModule::Get().GetSingleton();
#endif
#if defined WEBVIEW_CEF && !defined USING_WEBBROWSER
	ICEF3LIB::get()->LoadCEF3Modules();
#   if WITH_EDITOR 
	ICefCoreLIB::get()->Load();
#   endif
	webview::IBrowserInstance::Get().check_brand(ICEF3LIB::get()->Branch());
	webview::IBrowserInstance::Get().Load();
#   if WITH_EDITOR 
	FEditorDelegates::PausePIE.AddLambda([](bool) {webview::IBrowserInstance::Get().OnEndPIE(); });
	FEditorDelegates::BeginPIE.AddLambda([](bool) {webview::IBrowserInstance::Get().OnBeginPIE(); });
	FEditorDelegates::EndPIE.AddLambda([](bool) {webview::IBrowserInstance::Get().OnEndPIE(); });
	FEditorDelegates::ResumePIE.AddLambda([](bool) {webview::IBrowserInstance::Get().OnBeginPIE(); });
#   endif
#endif

#if WITH_EDITOR && 50100<=WEBVIEW_ENGINE_VERSION
	FGlobalTabmanager::Get()->RegisterTabSpawner(
		WebViewTabName, FOnSpawnTab::CreateRaw(this, &FWebViewModule::SpawnWebViewTab)
	)
		.SetDisplayName(FText::FromString("WebView"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetDeveloperToolsMiscCategory())
		.SetMenuType(ETabSpawnerMenuType::Enabled)
		.SetReuseTabMethod(FOnFindTabToReuse::CreateLambda(
			[](const FTabId&){return nullptr; }
		)) ;
	FWebViewCommands::Register();
	auto CommandList = MakeShared<FUICommandList>();
	CommandList->MapAction(
		FWebViewCommands::Get().OpenWebEditor,
		FExecuteAction::CreateRaw(this, &FWebViewModule::OpeWebViewTab)
	);

	UToolMenus* Menus = UToolMenus::Get();
	if (!Menus) return;

	static const TArray<FName> EditorMenus = {
	"MainFrame.MainMenu.Window"
	};
	UToolMenu* Menu;
	for (const FName& MenuName : EditorMenus){
		Menu = UToolMenus::Get()->ExtendMenu(MenuName);
		if (!Menu)continue;
		FToolMenuSection& Section = Menu->FindOrAddSection(TEXT("GetContent"));
		Section.AddMenuEntryWithCommandList(FWebViewCommands::Get().OpenWebEditor,CommandList);
	}
#endif
}

#if WITH_EDITOR && 50100<=WEBVIEW_ENGINE_VERSION
void FWebViewModule::OpeWebViewTab()
{
	FGlobalTabmanager::Get()->TryInvokeTab(WebViewTabName);
}
void FWebViewModule::AddMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Open Web View"),
		FText::FromString("Open Web View"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateRaw(
			this, &FWebViewModule::OpeWebViewTab))
	);
}

TSharedRef<SDockTab> FWebViewModule::SpawnWebViewTab(const FSpawnTabArgs&)
{
	TSharedPtr<SDockTab> docktab;
	TSharedPtr<SWebViewWidget> widget;
	SAssignNew(docktab,SDockTab)
		.TabRole(ETabRole::DocumentTab)
		[
			SAssignNew(widget,SWebViewWidget)
				.Visibility(EVisibility::Visible)
		];
	widget->SetDockTab(docktab);
	return docktab.ToSharedRef();
}
#endif

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWebViewModule, WebView)