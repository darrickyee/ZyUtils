// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZyAnimData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EModifyAnimMode : uint8
{
	Ignore,

	/** Add new value to input curve value */
	Add,

	/** Replace input value with new value */
	Replace
};

UENUM(BlueprintType)
enum class EModifyCurveMode : uint8
{

	/** Replace input value with new value */
	Replace,

	/** Add new value to input curve value */
	Add,

	/** Minimum of input value and new value */
	Min,

	/** Maximum of input value and new value */
	Max,

	/** Average of input value and new value */
	Average
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

static bool operator==(const FBoneModifier &A, const FBoneModifier &B)
{
	return A.BoneName == B.BoneName && A.Translation == B.Translation && A.TranslationMode == B.TranslationMode && A.TranslationSpace == B.TranslationSpace && A.Rotation == B.Rotation && A.RotationMode == B.RotationMode && A.RotationSpace == B.RotationSpace && A.Scale == B.Scale && A.ScaleMode == B.ScaleMode && A.ScaleSpace == B.ScaleSpace;
};

USTRUCT(BlueprintType)
struct FBoneModifierArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBoneModifier> BoneModifiers;
};

USTRUCT(BlueprintType)
struct FCurveModifier
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CurveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EModifyCurveMode> Mode;
};

USTRUCT(BlueprintType)
struct FCurveModifierArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCurveModifier> CurveModifiers;
};
