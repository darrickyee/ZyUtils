// Fill out your copyright notice in the Description page of Project Settings.

#include "ZyAnimNode_ModifyCurves.h"
#include "Animation/AnimInstanceProxy.h"
#include "AnimationRuntime.h"

FZyAnimNode_ModifyCurves::FZyAnimNode_ModifyCurves() : FAnimNode_Base()
{
	Mode = EModifyAnimMode::Add;
	Alpha = 1.f;
}

void FZyAnimNode_ModifyCurves::Initialize_AnyThread(const FAnimationInitializeContext &Context)
{
	ComponentPose.Initialize(Context);
}

void FZyAnimNode_ModifyCurves::Update_AnyThread(const FAnimationUpdateContext &Context)
{
	GetEvaluateGraphExposedInputs().Execute(Context);
	ComponentPose.Update(Context);
}

void FZyAnimNode_ModifyCurves::CacheBones_AnyThread(const FAnimationCacheBonesContext &Context)
{
	ComponentPose.CacheBones(Context);
}

void FZyAnimNode_ModifyCurves::EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext &Output)
{
	ComponentPose.EvaluateComponentSpace(Output);
	USkeleton *Skeleton = Output.AnimInstanceProxy->GetSkeleton();
	if (Skeleton)
	{
		const float a = FMath::Clamp(Alpha, 0.f, 1.f);

		for (int32 idx = 0; idx < CurveValueMap.CurveNames.Num(); idx++)
		{
			FName crvName = CurveValueMap.CurveNames[idx];
			SmartName::UID_Type crvUID = Skeleton->GetUIDByName(USkeleton::AnimCurveMappingName, crvName);

			if (crvUID != SmartName::MaxUID)
			{
				float crvValue = CurveValueMap.Values.IsValidIndex(idx) ? CurveValueMap.Values[idx] : 0.f;
				float lastCrvValue = Output.Curve.Get(crvUID);

				switch (Mode)
				{
				case EModifyAnimMode::Add:
					Output.Curve.Set(crvUID, a * crvValue + lastCrvValue);
					break;

				case EModifyAnimMode::Replace:
					Output.Curve.Set(crvUID, a * crvValue);
					break;

				default:
					break;
				}
			}
		}
	}
}