
#pragma once


#include "BaseRestFul.h"
#include "cef_export_macro.h"

class CEFBROWSER_DLL CCefRestFul 
	: public IBaseRestFul
	, public TSharedFromThis<CCefRestFul>
{
public:
	CCefRestFul();
	void Request(const FString& URL, const FMatureJsonValue& Data) override;
	virtual void BeginDestroy() override;
private:
	friend class CRestFulClient;
	TSharedPtr<struct RestFulData> resetful_data;
};
