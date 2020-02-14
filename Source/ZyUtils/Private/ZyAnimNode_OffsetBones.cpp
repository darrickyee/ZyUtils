// Fill out your copyright notice in the Description page of Project Settings.

#include "ZyAnimNode_OffsetBones.h"
#include "Animation/AnimInstanceProxy.h"
#include "AnimationRuntime.h"

FZyAnimNode_OffsetBones::FZyAnimNode_OffsetBones() : FAnimNode_Base(),
													 Space(EBoneControlSpace::BCS_BoneSpace)
{
}

void FZyAnimNode_OffsetBones::Initialize_AnyThread(const FAnimationInitializeContext &Context)
{
	ComponentPose.Initialize(Context);
}

void FZyAnimNode_OffsetBones::Update_AnyThread(const FAnimationUpdateContext &Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}

void FZyAnimNode_OffsetBones::CacheBones_AnyThread(const FAnimationCacheBonesContext &Context)
{
	ComponentPose.CacheBones(Context);
}

void FZyAnimNode_OffsetBones::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext &Output)
{
	ComponentPose.EvaluateComponentSpace(Output);

	if (BoneOffsets.BoneNames.Num() && BoneOffsets.BoneNames.Num() == BoneOffsets.Transforms.Num())
	{
		const FTransform ComponentTransform = Output.AnimInstanceProxy->GetComponentTransform();

		// TArray<FCompactPoseBoneIndex> InTransforms;
		TMap<int32, FTransform> InTransforms;

		InTransforms.Reset();

		const FCompactPose &CompactPose = Output.Pose.GetPose();
		const FBoneContainer &BoneContainer = CompactPose.GetBoneContainer();

		// Populate list of bones to be transformed
		for (int32 nameid = 0; nameid < BoneOffsets.BoneNames.Num(); nameid++)
		{
			int32 boneId = BoneContainer.GetPoseBoneIndexForBoneName(BoneOffsets.BoneNames[nameid]);

			if (boneId != INDEX_NONE && BoneOffsets.Transforms.IsValidIndex(nameid))
			{
				if (!BoneOffsets.Transforms[nameid].ContainsNaN())
				{
					InTransforms.Add(boneId, BoneOffsets.Transforms[nameid]);
				}
			}
		}

		if (InTransforms.Num())
		{

			TArray<int32> InBoneKeys;
			InTransforms.GetKeys(InBoneKeys);

			// Sort by hierarchy order
			InBoneKeys.Sort([BoneContainer](const int32 A, const int32 B) {
				return BoneContainer.BoneIsChildOf(B, A);
			});

			for (int32 boneid : InBoneKeys)
			{

				FTransform OutTransform = Output.Pose.GetComponentSpaceTransform(FCompactPoseBoneIndex(boneid));

				FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, OutTransform, FCompactPoseBoneIndex(boneid), Space);
				OutTransform *= InTransforms[boneid];
				FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, OutTransform, FCompactPoseBoneIndex(boneid), Space);

				Output.Pose.SetComponentSpaceTransform(FCompactPoseBoneIndex(boneid), OutTransform);
			}
		}
	}
}