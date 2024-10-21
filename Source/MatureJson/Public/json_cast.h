// Copyright aXiuShen. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "MatureJsonEnums.h"  // 包含 GetParseError_En 函数
#include "rapidjson/rapidjson.h"     // rapidjson's DOM-style API
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include <rapidjson/error/en.h>  // 包含 GetParseError_En 函数
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


namespace mature {

	template<typename >
	void print_type();

	template<typename T>
	class JsonChar {
	public:

	};

	template<>
	class JsonChar <char> : public rapidjson::UTF8<char> {
	public:
	};

	template<>
	class JsonChar <wchar_t> : public rapidjson::UTF16LE<wchar_t> {
	public:
	};

	template<>
	class JsonChar <char16_t> : public rapidjson::UTF16LE<char16_t> {
	public:
	};

	template<>
	class JsonChar <unsigned> : public rapidjson::UTF32LE<unsigned> {
	public:
	};


	typedef rapidjson::GenericStringRef<TCHAR> StringRefType;
	typedef rapidjson::GenericDocument<JsonChar<TCHAR> > Document;
	typedef rapidjson::GenericStringBuffer<JsonChar<TCHAR> > StringBuffer;
	typedef rapidjson::Writer<StringBuffer, JsonChar<TCHAR>, JsonChar<TCHAR>> Writer;
	typedef rapidjson::GenericValue<JsonChar<TCHAR> > Value;
	typedef rapidjson::GenericArray<false, Value > Array;
	typedef rapidjson::GenericArray<true, Value > ConstArray;
	typedef rapidjson::GenericObject<false, Value > Object;
	typedef rapidjson::GenericObject<true, Value > ConstObject;
	typedef rapidjson::GenericMemberIterator<false, JsonChar<TCHAR>, Document::AllocatorType> MemberIterator;
	typedef rapidjson::GenericMemberIterator<true, JsonChar<TCHAR>, Document::AllocatorType> ConstMemberIterator;

	//using Allocator = Document::AllocatorType;
	typedef Document::AllocatorType Allocator;
	using Type = rapidjson::Type;
	//using Array = Value::Array;
	//using ConstArray = Value::ConstArray;
	//using Object = Value::Object;
	//using ConstObject = Value::ConstObject;

	template<class T>
	T GetNumber(const Value& ValueRef) {
		if (mature::Type::kNumberType!=ValueRef.GetType())return T(0);
		if (ValueRef.IsDouble())return T(ValueRef.GetDouble());
		else if (ValueRef.IsInt64())return T(ValueRef.GetInt64());
		else if (ValueRef.IsUint64())return T(ValueRef.GetUint64());
		else if (ValueRef.IsInt())return T(ValueRef.GetInt());
		else if (ValueRef.IsUint())return T(ValueRef.GetUint());
		return T(0);
	}
	template<class T>
	bool GetNumberBool(const Value& ValueRef, T& value) {
		if (mature::Type::kNumberType != ValueRef.GetType())return false;
		if (ValueRef.IsDouble())value = T(ValueRef.GetDouble());
		else if (ValueRef.IsInt64())value = T(ValueRef.GetInt64());
		else if (ValueRef.IsUint64())value = T(ValueRef.GetUint64());
		else if (ValueRef.IsInt())value = T(ValueRef.GetInt());
		else if (ValueRef.IsUint())value = T(ValueRef.GetUint());
		else return false;
		return false;
	}

	template<class T>
	T GetNumberArray(const unsigned int idx,const Array& ArrayRef) {
		if (ArrayRef.Size() < idx)return T();
		return GetNumber<T>(ArrayRef[idx]);
	}
	FString GetString(const Value& ValueRef);
	bool GetStringBool(const Value& ValueRef, FString& value);
	FString GetStringArray(const unsigned int idx, const Array& ArrayRef);


}