// Fill out your copyright notice in the Description page of Project Settings.

#include "ZyAnimNode_ModifyBones.h"
#include "Animation/AnimInstanceProxy.h"
#include "AnimationRuntime.h"

FZyAnimNode_ModifyBones::FZyAnimNode_ModifyBones()
{
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

void FZyAnimNode_ModifyBones::ModifyTransform(int32 comp, FVector value, FTransform &Target, EModifyAnimMode Mode)
{
	if (Mode == EModifyAnimMode::Ignore)
		return;

	FQuat rot = FQuat(FRotator(value.Y, value.Z, value.X));

	switch (comp)
	{
	// Scale
	case 0:
		switch (Mode)
		{
		case EModifyAnimMode::Add:
			Target.MultiplyScale3D(value);
			return;

		case EModifyAnimMode::Replace:
			Target.SetScale3D(value);
			return;

		default:
			return;
		}

	case 1:

		switch (Mode)
		{
		case EModifyAnimMode::Add:
			Target.ConcatenateRotation(rot);
			Target.NormalizeRotation();
			return;

		case EModifyAnimMode::Replace:
			Target.SetRotation(rot);
			Target.NormalizeRotation();
			return;

		default:
			return;
		}

	case 2:
		switch (Mode)
		{
		case EModifyAnimMode::Add:
			Target.AddToTranslation(value);
			return;

		case EModifyAnimMode::Replace:
			Target.SetTranslation(value);
			return;

		default:
			return;
		}
	}
}

void FZyAnimNode_ModifyBones::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext &Output)
{
	ComponentPose.EvaluateComponentSpace(Output);

	if (BoneModifierArray.BoneModifiers.Num())
	{

		// Get pose and component data
		const FTransform ComponentTransform = Output.AnimInstanceProxy->GetComponentTransform();
		const FCompactPose &CompactPose = Output.Pose.GetPose();
		const FBoneContainer &BoneContainer = CompactPose.GetBoneContainer();

		// Map of Bone IDs to MBS values
		TMap<int32, FBoneModifier> BoneModMap;
		BoneModMap.Reset();

		// Populate list of bones to be modified
		for (FBoneModifier mbs : BoneModifierArray.BoneModifiers)
		{
			int32 boneId = BoneContainer.GetPoseBoneIndexForBoneName(mbs.BoneName);

			if (boneId != INDEX_NONE)
			{
				BoneModMap.Add(boneId, mbs);
			}
		}

		if (BoneModMap.Num())
		{
			float a = FMath::Clamp(Alpha, 0.f, 1.f);

			// Sort keys by hierarchy
			TArray<int32> BoneKeys;
			BoneModMap.GetKeys(BoneKeys);
			BoneKeys.Sort([BoneContainer](const int32 A, const int32 B) {
				return BoneContainer.BoneIsChildOf(B, A);
			});

			// Modify transforms in order
			for (int32 boneId : BoneKeys)
			{
				// Target transform copy
				FTransform OutTransform = Output.Pose.GetComponentSpaceTransform(FCompactPoseBoneIndex(boneId));

				FBoneModifier mbs = BoneModMap[boneId];

				// 0: Scale, 1: Rotate, 2: Translate
				for (int32 comp = 0; comp < 3; ++comp)
				{
					FVector values = FVector(0.0);
					EModifyAnimMode mode = EModifyAnimMode::Ignore;
					EBoneControlSpace space = EBoneControlSpace::BCS_WorldSpace;

					switch (comp)
					{
					case 0:
						values = mbs.Scale;
						mode = mbs.ScaleMode;
						space = mbs.ScaleSpace;
						break;

					case 1:
						values = FVector(mbs.Rotation.Roll, mbs.Rotation.Pitch, mbs.Rotation.Yaw);
						mode = mbs.RotationMode;
						space = mbs.RotationSpace;
						break;

					case 2:
						values = mbs.Translation;
						mode = mbs.TranslationMode;
						space = mbs.TranslationSpace;
						break;
					}

					FAnimationRuntime::ConvertCSTransformToBoneSpace(ComponentTransform, Output.Pose, OutTransform, FCompactPoseBoneIndex(boneId), space);

					ModifyTransform(comp, values, OutTransform, mode);

					FAnimationRuntime::ConvertBoneSpaceTransformToCS(ComponentTransform, Output.Pose, OutTransform, FCompactPoseBoneIndex(boneId), space);
				}

				OutTransform.BlendWith(Output.Pose.GetComponentSpaceTransform(FCompactPoseBoneIndex(boneId)), 1 - a);
				Output.Pose.SetComponentSpaceTransform(FCompactPoseBoneIndex(boneId), OutTransform);
			}
		}
	}
}