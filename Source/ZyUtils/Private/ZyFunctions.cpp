// Fill out your copyright notice in the Description page of Project Settings.

#include "ZyFunctions.h"

void UZyFunctions::MakeBoneOffsets(const TMap<FName, FTransform> OffsetMap, FBoneOffsets &BoneOffsets)
{
	TArray<FName> BoneNames;
	TArray<FTransform> Transforms;

	for (auto &entry : OffsetMap)
	{
		BoneNames.Add(entry.Key);
		Transforms.Add(entry.Value.ContainsNaN() ? FTransform::Identity : entry.Value);
	}

	BoneOffsets.BoneNames = BoneNames;
	BoneOffsets.Transforms = Transforms;
}