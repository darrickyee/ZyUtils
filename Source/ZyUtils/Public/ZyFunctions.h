// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZyFunctions.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType, meta = (HasNativeMake="ZyUtils.ZyFunctions.MakeBoneOffsets"))
struct FBoneOffsets
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> BoneNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTransform> Transforms;
};

UCLASS()
class ZYUTILS_API UZyFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Convert a Name: Transform mapping for use with OffsetBones anim node.
	UFUNCTION(BlueprintPure, Category = "ZyUtils", meta = (NativeMakeFunc, BlueprintThreadSafe))
		static void MakeBoneOffsets(const TMap<FName, FTransform> OffsetMap, FBoneOffsets &BoneOffsets);
};
