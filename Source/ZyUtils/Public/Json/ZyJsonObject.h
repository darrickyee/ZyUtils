// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Dom/JsonObject.h"
#include "Json/ZyJsonValue.h"

#include "CoreMinimal.h"
#include "ZyJsonObject.generated.h"

USTRUCT(BlueprintType)
struct ZYUTILS_API FZyJsonObject
{
	GENERATED_USTRUCT_BODY()

public:

	friend class UZyJsonUtils;

	FZyJsonObject() : JsonObject(MakeShareable(new FJsonObject())) {};

	void SetValue(const FString& Key, const FZyJsonValue& Value);

	FZyJsonValue GetValue(const FString& Key);

protected:
	TSharedPtr<FJsonObject> JsonObject;
};