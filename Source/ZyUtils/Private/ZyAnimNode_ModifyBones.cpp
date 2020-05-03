// Fill out your copyright notice in the Description page of Project Settings.

#include "ZyAnimNode_ModifyBones.h"
#include "Animation/AnimInstanceProxy.h"
#include "AnimationRuntime.h"

FZyAnimNode_ModifyBones::FZyAnimNode_ModifyBones()
{
	Space = EBoneControlSpace::BCS_BoneSpace;
	Mode = EModifyAnimMode::Add;
	Alpha = 1.f;
}

void FZyAnimNode_ModifyBones::Initialize_AnyThread(const FAnimationInitializeContext &Context)
{
	ComponentPose.Initialize(Context);
}

void FZyAnimNode_ModifyBones::Update_AnyThread(const FAnimationUpdateContext &Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}

void FZyAnimNode_ModifyBones::CacheBones_AnyThread(const FAnimationCacheBonesContext &Context)
{
	ComponentPose.CacheBones(Context);
}

void FZyAnimNode_ModifyBones::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext &Output)
{
	ComponentPose.EvaluateComponentSpace(Output);

	if (BoneTransformMap.BoneNames.Num())
	{
		const FTransform ComponentTransform = Output.AnimInstanceProxy->GetComponentTransform();

		// TArray<FCompactPoseBoneIndex> InTransforms;
		TMap<int32, FTransform> InTransforms;

		InTransforms.Reset();

		const FCompactPose &CompactPose = Output.Pose.GetPose();
		const FBoneContainer &BoneContainer = CompactPose.GetBoneContainer();

		// Populate list of bones to be transformed
		for (int32 idx = 0; idx < BoneTransformMap.BoneNames.Num(); idx++)
		{
			int32 boneId = BoneContainer.GetPoseBoneIndexForBoneName(BoneTransformMap.BoneNames[idx]);

			if (boneId != INDEX_NONE && BoneTransformMap.Transforms.IsValidIndex(idx))
			{
				if (!BoneTransformMap.Transforms[idx].ContainsNaN())
				{
					InTransforms.Add(boneId, BoneTransformMap.Transforms[idx]);
				}
			}
		}

		if (InTransforms.Num())
		{
			float a = FMath::Clamp(Alpha, 0.f, 1.f);

			TArray<int32> InBoneKeys;
			InTransforms.GetKeys(InBoneKeys);

			// Sort by hierarchy order
			InBoneKeys.Sort([BoneContainer](const int32 A, const int32 B) {
				return BoneContainer.BoneIsChildOf(B, A);
			});

			for (int32 boneid : InBoneKeys)
			{

				// Current transform
				FTransform OutTransform = Output.Pose.GetComponentSpaceTransform(FCompactPoseBoneIndex(boneid));
				FTransform InTransform = InTransforms[boneid];
				InTransform.BlendWith(FTransform::Identity, 1 - a);

				FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, OutTransform, FCompactPoseBoneIndex(boneid), Space);

				switch (Mode)
				{
				case EModifyAnimMode::Add:
					OutTransform *= InTransform;
					break;

				case EModifyAnimMode::Replace:
					OutTransform = InTransform;
					break;
				}

				FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, OutTransform, FCompactPoseBoneIndex(boneid), Space);

				Output.Pose.SetComponentSpaceTransform(FCompactPoseBoneIndex(boneid), OutTransform);
			}
		}
	}
}