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
	Ignore,

	/** Add new value to input curve value */
	Add,

	/** Replace input value with new value */
	Replace
};

USTRUCT(BlueprintType)
struct FBoneModifier
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Translation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EModifyAnimMode> TranslationMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EBoneControlSpace> TranslationSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EModifyAnimMode> RotationMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EBoneControlSpace> RotationSpace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EModifyAnimMode> ScaleMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EBoneControlSpace> ScaleSpace;
};

USTRUCT(BlueprintType)
struct FBoneModifierArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBoneModifier> BoneModifiers;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "ZyUtils.ZyFunctions.MakeBoneTransformMap", HasNativeBreak = "ZyUtils.ZyFunctions.BreakBoneTransformMap"))
struct FBoneTransformMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> BoneNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTransform> Transforms;
};

USTRUCT(BlueprintType, meta = (HasNativeMake = "ZyUtils.ZyFunctions.MakeCurveValueMap", HasNativeBreak = "ZyUtils.ZyFunctions.BreakCurveValueMap"))
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
	// Transform mapping for use with OffsetBones anim node.
	UFUNCTION(BlueprintPure, Category = "ZyUtils", meta = (NativeMakeFunc, BlueprintThreadSafe))
	static void MakeBoneTransformMap(const TMap<FName, FTransform> TransformMap, FBoneTransformMap &BoneTransformMap);

	UFUNCTION(BlueprintPure, Category = "ZyUtils", meta = (NativeBreakFunc, BlueprintThreadSafe))
	static void BreakBoneTransformMap(const FBoneTransformMap BoneTransformMap, TMap<FName, FTransform> &TransformMap);

	// Transform mapping for use with SetCurves anim node.
	UFUNCTION(BlueprintPure, Category = "ZyUtils", meta = (NativeMakeFunc, BlueprintThreadSafe))
	static void MakeCurveValueMap(const TMap<FName, float> CurveMap, FCurveValueMap &CurveValueMap);

	UFUNCTION(BlueprintPure, Category = "ZyUtils", meta = (NativeBreakFunc, BlueprintThreadSafe))
	static void BreakCurveValueMap(const FCurveValueMap CurveValueMap, TMap<FName, float> &CurveMap);
};
