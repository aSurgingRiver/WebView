// Copyright aXiuShen. All Rights Reserved.

#include "MatureJsonModule.h"
#include "MatureJsonLog.h"
#include "json_cast.h"
#include "MatureJsonValue.h"
#include "MatureJsonObject.h"
#include "MatureJsonArray.h"


#define LOCTEXT_NAMESPACE "FBaseBrowserModule"

DEFINE_LOG_CATEGORY(MatureJsonLog);

FString value_to_string (FMatureJsonValue Value) {
	// 任意 value节点 均可以序列化字符串
	FString sub_string = Value.ToObject().GetValue(TEXT("小说情侣")).SaveString();
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

void list_encode_example(FMatureJsonArray List) {
	FMatureJsonObject Object;
	Object = List.AddObject();
	Object.SetArray(TEXT("省份"))
		.AddValue(TEXT("北京"))
		.AddValue(TEXT("香港"))
		.AddValue(TEXT("澳门"))
		.AddValue(TEXT("台湾省"))
		.AddValue(TEXT("四川"));
	FMatureJsonObject Object2 /*= List.AddObject()*/;
	Object2.SetArray(TEXT("艺术家"))
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
	FMatureJsonArray List;
	TMap<FString, double> map_doble = { {TEXT("w"),123.0},{TEXT("e"),123.0},{TEXT("r"),123.0} };
	TMap<FString, FString> map_string = { {TEXT("郭靖"),TEXT("黄蓉")},{TEXT("杨过"),TEXT("小龙女")} };
	Value.ToObject()
		.SetValue(TEXT("alpha"), 0.25)
		.SetValue(TEXT("悟空租车"), TEXT("自驾游"))
		.SetValue(TEXT("color"), 0x00FFFFFF)
		.SetValue(TEXT("爱好和平"), true)
		.SetValue(TEXT("当前时间"), FDateTime::Now());
	Object = Value.ToObject()
		.SetObject(TEXT("对象属性"));
	Object.AddValue(map_doble);

	Object3.AddValue(map_string);
	Object2 = Value.ToObject()
		.SetObject(TEXT("小说情侣"))
		.AddValue(Object3);


	list_encode_example(List);
	Value.ToObject()
		.SetValue(TEXT("中国"), List);

	return Value;
}

void decode_example(FMatureJsonValue Root) {
	FMatureJsonObject Object = Root.ToObject();
	float alpha = Object.GetValue(TEXT("alpha")).ToFloat();
	int32 color = Object.GetValue(TEXT("color")).ToInt32();
	FMatureJsonArray china = Object.GetArray(TEXT("中国"));
	FString china_str = Object.GetValue(TEXT("中国")).SaveString();
	FMatureJsonArray list_province = china.GetObject(0).GetArray(TEXT("省份"));
	FString province_str = china.GetObject(0).GetValue(TEXT("省份")).SaveString();
	FString taiwan_province = list_province.GetValue(3).ToString();
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