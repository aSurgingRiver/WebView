// Copyright aXiuShen. All Rights Reserved.
#pragma once
#include <vector>

#ifdef WEBVIEW_CEF
class  ICefCoreLIB {
public:
	static ICefCoreLIB* get();
	virtual bool can_load() = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
};
#endif


