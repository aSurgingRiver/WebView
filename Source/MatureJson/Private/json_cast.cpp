
#include "json_cast.hpp"
#include <iostream>
#include <string>

namespace mature {
	
	template<typename T>
	void print_type() {
		std::cout << "unkown" << std::endl;
	}
	template<>
	void print_type<char>() {
		std::cout << "char" << std::endl;
	}
	template<>
	void print_type<wchar_t>() {
		std::cout << "wchar_t" << std::endl;
	}
	template<>
	void print_type<unsigned char>() {
		std::cout << "UTF8CHAR" << std::endl;
	}
	template<>
	void print_type<unsigned short int>() {
		std::cout << "uint16_t" << std::endl;
	}
	template<>
	void print_type<unsigned int>() {
		std::cout << "uint32_t" << std::endl;
	}


	FString GetString(const Value& ValueRef) {
		switch (ValueRef.GetType())
		{
		case mature::Type::kFalseType: return TEXT("false");
		case mature::Type::kTrueType:  return TEXT("true");
		case mature::Type::kNumberType: return FString::SanitizeFloat(mature::GetNumber<float>(ValueRef), 0);
		case mature::Type::kStringType: return FString(ValueRef.GetString());
		}
		return FString();
	}
	bool GetStringBool(const Value& ValueRef, FString& value) {
		switch (ValueRef.GetType())
		{
		case mature::Type::kFalseType: value = TEXT("false"); break;
		case mature::Type::kTrueType:  value = TEXT("true"); break;
		case mature::Type::kNumberType: value = FString::SanitizeFloat(mature::GetNumber<float>(ValueRef), 0); break;
		case mature::Type::kStringType: value = FString(ValueRef.GetString()); break;
		default: return false;
		}
		return true;
	}
	FString GetStringArray(const unsigned int idx, const Array& ArrayRef) {
		if (ArrayRef.Size() < idx)return FString();
		return GetString(ArrayRef[idx]);
	}

}

