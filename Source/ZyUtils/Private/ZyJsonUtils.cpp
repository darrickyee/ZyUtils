// Fill out your copyright notice in the Description page of Project Settings.


#include "ZyJsonUtils.h"

void UZyJsonUtils::IsValid(const FZyJsonValue& Json, bool& Valid)
{
	Valid = Json.JsonValue.IsValid() && Json.JsonValue->Type != EJson::None;
}