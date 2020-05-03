// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZyFunctions.generated.h"

/**
 * 
 */

UENUM()
enum class EModifyAnimMode : uint8
{
	/** Add new value to input curve value */
	Add,

	/** Replace input value with new value */
	Replace
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "ZyUtils.ZyFunctions.MakeBoneTransformMap"))
struct FBoneTransformMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> BoneNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTransform> Transforms;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "ZyUtils.ZyFunctions.MakeCurveValueMap"))
struct FCurveValueMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> CurveNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> Values;
};

UCLASS()
class ZYUTILS_API UZyFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Convert a Name: Transform mapping for use with OffsetBones anim node.
	UFUNCTION(BlueprintPure, Category = "ZyUtils", meta = (NativeMakeFunc, BlueprintThreadSafe))
	static void MakeBoneTransformMap(const TMap<FName, FTransform> TransformMap, FBoneTransformMap &BoneTransformMap);

	// Convert a Name: Transform mapping for use with SetCurves anim node.

	UFUNCTION(BlueprintPure, Category = "ZyUtils", meta = (NativeMakeFunc, BlueprintThreadSafe))
	static void MakeCurveValueMap(const TMap<FName, float> CurveMap, FCurveValueMap &CurveValueMap);
};
