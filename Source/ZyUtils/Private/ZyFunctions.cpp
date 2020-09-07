// Fill out your copyright notice in the Description page of Project Settings.

#include "ZyFunctions.h"

void UZyFunctions::MakeBoneTransformMap(const TMap<FName, FTransform> TransformMap, FBoneTransformMap &BoneTransformMap)
{
	TArray<FName> BoneNames;
	TArray<FTransform> Transforms;

	for (auto &entry : TransformMap)
	{
		BoneNames.Add(entry.Key);
		Transforms.Add(entry.Value.ContainsNaN() ? FTransform::Identity : entry.Value);
	}

	BoneTransformMap.BoneNames = BoneNames;
	BoneTransformMap.Transforms = Transforms;
}

void UZyFunctions::BreakBoneTransformMap(const FBoneTransformMap BoneTransformMap, TMap<FName, FTransform> &TransformMap)
{
	TArray<FName> BoneNames = BoneTransformMap.BoneNames;
	TArray<FTransform> Transforms = BoneTransformMap.Transforms;

	for (int32 i = 0; i != BoneNames.Num(); ++i)
	{
		const FTransform xform = i < Transforms.Num() ? Transforms[i] : FTransform::Identity;
		TransformMap.Add(BoneNames[i], xform);
	}
}

void UZyFunctions::MakeCurveValueMap(const TMap<FName, float> CurveMap, FCurveValueMap &CurveValueMap)
{
	TArray<FName> CurveNames;
	TArray<float> Values;

	for (auto &entry : CurveMap)
	{
		CurveNames.Add(entry.Key);
		Values.Add(isnan(entry.Value) ? 0.0 : entry.Value);
	}

	CurveValueMap.CurveNames = CurveNames;
	CurveValueMap.Values = Values;
}

void UZyFunctions::BreakCurveValueMap(const FCurveValueMap CurveValueMap, TMap<FName, float> &CurveMap)
{
	TArray<FName> CurveNames = CurveValueMap.CurveNames;
	TArray<float> Values = CurveValueMap.Values;

	for (int32 i = 0; i != CurveNames.Num(); ++i)
	{
		const float val = i < Values.Num() ? Values[i] : 0.0;
		CurveMap.Add(CurveNames[i], val);
	}
}