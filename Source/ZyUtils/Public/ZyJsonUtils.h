// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Json/ZyJsonValue.h"
#include "Json/ZyJsonObject.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZyJsonUtils.generated.h"

/**
 * 
 */
UCLASS()
class ZYUTILS_API UZyJsonUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "JSON Utilities")
	static void IsValid(const FZyJsonValue& Json, bool& Valid);

	UFUNCTION(BlueprintPure, Category = "JSON Utilities")
	static void GetType(const FZyJsonValue& Value, EZyJsonType& JsonType) { JsonType = Value.GetType(); };

	UFUNCTION(BlueprintPure, Category = "JSON Utilities")
	static void FromBool(const bool Value, FZyJsonValue& JsonValue) { JsonValue = FZyJsonValue(Value); };

	UFUNCTION(BlueprintPure, Category = "JSON Utilities")
	static void FromInt(const int Value, FZyJsonValue& JsonValue) { JsonValue = FZyJsonValue(Value); };

	UFUNCTION(BlueprintPure, Category = "JSON Utilities")
	static void FromFloat(const float Value, FZyJsonValue& JsonValue) { JsonValue = FZyJsonValue(Value); };

	UFUNCTION(BlueprintPure, Category = "JSON Utilities")
	static void FromString(const FString& Value, FZyJsonValue& JsonValue) { JsonValue = FZyJsonValue(Value); };

	UFUNCTION(BlueprintPure, Category = "JSON Utilities")
	static void FromObject(const FZyJsonObject& Object, FZyJsonValue& JsonValue)
	{
		JsonValue = Object.JsonObject.IsValid() ? FZyJsonValue(Object.JsonObject) : FZyJsonValue();
	};

	UFUNCTION(BlueprintCallable, Category = "JSON Utilities")
	static void CreateObject(FZyJsonObject& JsonObject) { JsonObject = FZyJsonObject(); };

	UFUNCTION(BlueprintPure, Category = "JSON Utilities")
	static void GetValue(const FZyJsonObject& JsonObject, const FString& Key, FZyJsonValue& JsonValue)
	{
		JsonValue = JsonObject.GetValue(Key);
	}

	UFUNCTION(BlueprintCallable, Category = "JSON Utilities")
	static void SetValue(const FZyJsonObject& JsonObject, const FString& Key, const FZyJsonValue& JsonValue)
	{
		JsonObject.SetValue(Key, JsonValue);
	}

	UFUNCTION(BlueprintPure, Category="JSON Utilities")
	static void ParseJSON(const FString& JsonString, FZyJsonValue& JsonValue, bool& Success);

	UFUNCTION(BlueprintPure, Category="JSON Utilities")
    static void StringifyJSON(const FZyJsonValue& JsonValue, FString& JsonString,  bool& Success);

};
