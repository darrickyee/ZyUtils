// Fill out your copyright notice in the Description page of Project Settings.


#include "ZyJsonUtils.h"

void UZyJsonUtils::IsValid(const FZyJsonValue& Json, bool& Valid)
{
	Valid = Json.JsonValue.IsValid() && Json.JsonValue->Type != EJson::None;
}

void UZyJsonUtils::ParseJSON(const FString& JsonString, FZyJsonValue& JsonValue, bool& Success)
{
	FString Input = JsonString.TrimStart().TrimEnd();
	if (Input.IsEmpty()) return;

	const bool isPrimitive = !(Input.StartsWith("{") || Input.StartsWith("["));
	if (isPrimitive) Input = "[" + Input + "]";

	const TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Input);

	Success = FJsonSerializer::Deserialize(Reader, JsonValue.JsonValue) && JsonValue.JsonValue.IsValid();
		
	// Return null value (with valid pointer) if failed to parse
	if (!Success)
	{
		JsonValue = FZyJsonValue();
		return;
	}

	// Pull primitive value from array if primitive
	if (isPrimitive)
	{
		JsonValue = FZyJsonValue(JsonValue.JsonValue->AsArray()[0]);
	}
}

void UZyJsonUtils::StringifyJSON(const FZyJsonValue& JsonValue, FString& JsonString, bool& Success)
{
	// Null pointer or None -> return
	if (JsonValue.GetType() == EZyJsonType::None) return;

	const TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<
		TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&JsonString);

	// Wrap value in array in case it's a primitive
	const TArray<TSharedPtr<FJsonValue>> ValueArray = {JsonValue.JsonValue};
	// TODO: Handle bugged exception with empty string as object key
	Success = FJsonSerializer::Serialize(ValueArray, Writer);

	if (!Success)
	{
		JsonString = "";
		return;
	}

	// Trim array brackets
	JsonString = JsonString.Mid(1, JsonString.Len() - 2).ReplaceEscapedCharWithChar();
}
