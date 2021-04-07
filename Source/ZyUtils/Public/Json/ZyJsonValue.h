// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Dom/JsonValue.h"
#include "ZyJsonTypes.h"

#include "CoreMinimal.h"
#include "ZyJsonValue.generated.h"

USTRUCT(BlueprintType)
struct ZYUTILS_API FZyJsonValue
{
	GENERATED_USTRUCT_BODY()

public:

	friend class UZyJsonUtils;
	friend class FZyJsonObject;

	FZyJsonValue() : JsonValue(MakeShareable(new FJsonValueNull())) {};
	FZyJsonValue(bool InValue) : JsonValue(MakeShareable(new FJsonValueBoolean(InValue))) {};
	FZyJsonValue(int32 InValue) : FZyJsonValue((float)InValue) {};
	FZyJsonValue(float InValue) : JsonValue(MakeShareable(new FJsonValueNumber(InValue))) {};
	FZyJsonValue(const char* InValue) : FZyJsonValue(FString(InValue)) {};
	FZyJsonValue(const FString &InValue) : JsonValue(MakeShareable(new FJsonValueString(InValue))) {};
	FZyJsonValue(const TSharedPtr<FJsonObject> InValue) : JsonValue(MakeShareable(new FJsonValueObject(InValue))) {};

	EZyJsonType GetType() const;

protected:
	TSharedPtr<FJsonValue> JsonValue;
};