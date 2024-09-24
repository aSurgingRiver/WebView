// Copyright aXiuShen. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/SlateDelegates.h"
#include "WebCookie.generated.h"

USTRUCT(BlueprintType)
struct BASEBROWSER_API FWebCookie
{
	GENERATED_USTRUCT_BODY()
	// The cookie name.
	UPROPERTY(BlueprintReadWrite, Category = "Web View")
	FString Name;

	// The cookie value.
	UPROPERTY(BlueprintReadWrite, Category = "Web View")
	FString Value;

	// If is empty a host cookie will be created instead of a domain
	// cookie. Domain cookies are stored with a leading "." and are visible to
	// sub-domains whereas host cookies are not.
	UPROPERTY(BlueprintReadWrite, Category = "Web View")
	FString Domain;

	// If is non-empty only URLs at or below the path will get the cookie
	// value.
	UPROPERTY(BlueprintReadWrite, Category = "Web View")
	FString Path;

	// If true the cookie will only be sent for HTTPS requests.
	UPROPERTY(BlueprintReadWrite, Category = "Web View")
	bool bSecure=false;

	// If true the cookie will only be sent for HTTP requests.
	UPROPERTY(BlueprintReadWrite, Category = "Web View")
	bool bHttpOnly=false;

	// If true the cookie will expire at the specified Expires datetime.
	UPROPERTY(BlueprintReadWrite, Category = "Web View")
	bool bHasExpires=false;

	// The cookie expiration date is only valid if bHasExpires is true.
	UPROPERTY(BlueprintReadWrite, Category = "Web View")
	FDateTime Expires;
};
