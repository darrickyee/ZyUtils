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
		TArray<FBoneModifier> bma = BoneModifierArray.BoneModifiers;

		// Populate list of bones to be modified
		const FBoneContainer &BoneContainer = Output.Pose.GetPose().GetBoneContainer();

		TArray<FBoneModifier> Modifiers;
		TMap<FName, int32> BoneIdMap;

		for (FBoneModifier boneMod : bma)
		{
			int32 boneId = BoneContainer.GetPoseBoneIndexForBoneName(boneMod.BoneName);

			if (boneId != INDEX_NONE)
			{
				Modifiers.Add(boneMod);
				BoneIdMap.Add(boneMod.BoneName, boneId);
			}
		}

		if (Modifiers.Num())
		{
			float a = FMath::Clamp(Alpha, 0.f, 1.f);

			// Get pose and component data
			const FTransform ComponentTransform = Output.AnimInstanceProxy->GetComponentTransform();

			// Sort keys by hierarchy
			Modifiers.Sort([BoneContainer, BoneIdMap, bma](FBoneModifier A, FBoneModifier B) {
				if (A.BoneName == B.BoneName)
					return bma.Find(A) < bma.Find(B);

				return BoneContainer.BoneIsChildOf(BoneIdMap[B.BoneName], BoneIdMap[A.BoneName]);
			});

			// Modify transforms in order
			for (FBoneModifier boneMod : Modifiers)
			{
				int32 boneId = BoneContainer.GetPoseBoneIndexForBoneName(boneMod.BoneName);
				// Target transform copy
				FTransform OutTransform = Output.Pose.GetComponentSpaceTransform(FCompactPoseBoneIndex(boneId));

				// 0: Scale, 1: Rotate, 2: Translate
				for (int32 comp = 0; comp < 3; ++comp)
				{
					FVector values = FVector(0.0);
					EModifyAnimMode mode = EModifyAnimMode::Ignore;
					EBoneControlSpace space = EBoneControlSpace::BCS_WorldSpace;

					switch (comp)
					{
					case 0:
						values = boneMod.Scale;
						mode = boneMod.ScaleMode;
						space = boneMod.ScaleSpace;
						break;

					case 1:
						values = FVector(boneMod.Rotation.Roll, boneMod.Rotation.Pitch, boneMod.Rotation.Yaw);
						mode = boneMod.RotationMode;
						space = boneMod.RotationSpace;
						break;

					case 2:
						values = boneMod.Translation;
						mode = boneMod.TranslationMode;
						space = boneMod.TranslationSpace;
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

		Modifiers.Empty();
		BoneIdMap.Empty();
		bma.Empty();
	}
}