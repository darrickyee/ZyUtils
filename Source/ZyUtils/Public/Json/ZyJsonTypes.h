// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZyJsonTypes.generated.h"

UENUM(BlueprintType)
enum class EZyJsonType : uint8
{
	None,
	Null,
	String,
	Number,
	Boolean,
	Array,
	Object
};