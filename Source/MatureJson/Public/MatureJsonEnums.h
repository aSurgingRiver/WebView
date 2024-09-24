// Copyright 2024 Tracer Interactive, LLC. All Rights Reserved.
#pragma once
#include "MatureJsonEnums.generated.h"

UENUM(BlueprintType, meta = (DisplayName = "Mature Json|Type"))
enum class EMatureJsonType : uint8
{
	Null		    UMETA(DisplayName = "Null"),
	Bool  			UMETA(DisplayName = "Bool"),
	Number  		UMETA(DisplayName = "Number"),
	String			UMETA(DisplayName = "String"),
	Object 			UMETA(DisplayName = "Object"),
	Array		    UMETA(DisplayName = "Array"),
};

enum class EMatureJsonTypeNumber : uint8
{
	Unkown		    UMETA(DisplayName = "Unkown"),
	Double		    UMETA(DisplayName = "Double"),
	Int32  			UMETA(DisplayName = "Int32"),
	Uint32 			UMETA(DisplayName = "Uint32"),
	Int64			UMETA(DisplayName = "Int64"),
	Uint64 			UMETA(DisplayName = "Uint64"),
};
