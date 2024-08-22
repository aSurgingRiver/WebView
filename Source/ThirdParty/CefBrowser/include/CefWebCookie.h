// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/SlateDelegates.h"
#include "warp_macro.h"

namespace webview {
	struct FWebCookie
	{
		// The cookie name.
		FString Name;

		// The cookie value.
		FString Value;

		// If is empty a host cookie will be created instead of a domain
		// cookie. Domain cookies are stored with a leading "." and are visible to
		// sub-domains whereas host cookies are not.
		FString Domain;

		// If is non-empty only URLs at or below the path will get the cookie
		// value.
		FString Path;

		// If true the cookie will only be sent for HTTPS requests.
		bool bSecure = false;

		// If true the cookie will only be sent for HTTP requests.
		bool bHttpOnly = false;

		// If true the cookie will expire at the specified Expires datetime.
		bool bHasExpires = false;

		// The cookie expiration date is only valid if bHasExpires is true.
		FDateTime Expires;
	};
}