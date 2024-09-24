// Copyright aXiuShen. All Rights Reserved.

#include "MatureJsonModule.h"
#include "MatureJsonLog.h"
#include "json_cast.hpp"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonList.h"


#define LOCTEXT_NAMESPACE "FBaseBrowserModule"

DEFINE_LOG_CATEGORY(MatureJsonLog);

FString value_to_string (FMatureJsonValue Value) {
	// 任意 value节点 均可以序列化字符串
	FString sub_string = Value.ToObject().ToValue(TEXT("小说情侣")).SaveString();
	// 跟节点 做序列化
	FString root_string = Value.SaveString();

	return root_string;
}

FString value_object_loop (FMatureJsonValue Value) {
	EMatureJsonType type;
	FString Key;
	FMatureJsonObjectIterator it = Value.ToObject();
	for (; it.IsValid(); it++) {
		Key = it.Key();
		type = it.Value().GetType();
	}
	return FString();
}

void list_encode_example(FMatureJsonList List) {
	FMatureJsonObject Object;
	Object = List.AddObject();
	Object.AddList(TEXT("省份"))
		.AddValue(TEXT("北京"))
		.AddValue(TEXT("香港"))
		.AddValue(TEXT("澳门"))
		.AddValue(TEXT("台湾省"))
		.AddValue(TEXT("四川"));
	FMatureJsonObject Object2 /*= List.AddObject()*/;
	Object2.AddList(TEXT("艺术家"))
		.AddValue(TEXT("陈道明"))
		.AddValue(TEXT("成龙"))
		.AddValue(TEXT("刘德华"))
		.AddValue(TEXT("张艺谋"))
		.AddValue(TEXT("刀郎"));
	List.AddValue(Object2);
}

FMatureJsonValue object_encode_example() {
	FMatureJsonValue Value;
	FMatureJsonObject Object;
	FMatureJsonObject Object2;
	FMatureJsonObject Object3;
	FMatureJsonList List;
	TMap<FString, double> map_doble = { {TEXT("w"),123.0},{TEXT("e"),123.0},{TEXT("r"),123.0} };
	TMap<FString, FString> map_string = { {TEXT("郭靖"),TEXT("黄蓉")},{TEXT("杨过"),TEXT("小龙女")} };
	Value.ToObject()
		.AddValue(TEXT("alpha"), 0.25)
		.AddValue(TEXT("悟空租车"), TEXT("自驾游"))
		.AddValue(TEXT("color"), 0x00FFFFFF)
		.AddValue(TEXT("爱好和平"), true)
		.AddValue(TEXT("当前时间"), FDateTime::Now());
	Object = Value.ToObject()
		.AddObject(TEXT("对象属性"));
	Object.AddValue(map_doble);

	Object3.AddValue(map_string);
	Object2 = Value.ToObject()
		.AddObject(TEXT("小说情侣"))
		.AddValue(Object3);


	list_encode_example(List);
	Value.ToObject()
		.AddValue(TEXT("中国"), List);

	return Value;
}

void decode_example(FMatureJsonValue Root) {
	FMatureJsonObject Object = Root.ToObject();
	float alpha = Object.ToValue(TEXT("alpha")).ToFloat();
	int32 color = Object.ToValue(TEXT("color")).ToInt32();
	FMatureJsonList china = Object.ToList(TEXT("中国"));
	FString china_str = Object.ToValue(TEXT("中国")).SaveString();
	FMatureJsonList list_province = china.ToObject(0).ToList(TEXT("省份"));
	FString province_str = china.ToObject(0).ToValue(TEXT("省份")).SaveString();
	FString taiwan_province = list_province.ToValue(3).ToString();
	taiwan_province.Append(TEXT(""));
}

void FMatureJsonModule::StartupModule()
{
#if WITH_EDITOR
	FMatureJsonValue Value = object_encode_example();

	value_to_string(Value);

	decode_example(Value);

	value_object_loop(Value);
#endif
}

void FMatureJsonModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMatureJsonModule, MatureJson)