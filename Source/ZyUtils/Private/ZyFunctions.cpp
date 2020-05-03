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