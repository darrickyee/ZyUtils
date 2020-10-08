// Fill out your copyright notice in the Description page of Project Settings.

#include <algorithm>
#include "ZyAnimNode_ModifyCurves.h"
#include "Animation/AnimInstanceProxy.h"
#include "AnimationRuntime.h"

FZyAnimNode_ModifyCurves::FZyAnimNode_ModifyCurves() : FAnimNode_Base()
{
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

		for (FCurveModifier crvmod : CurveModifierArray.CurveModifiers)
		// for (int32 idx = 0; idx < CurveValueMap.CurveNames.Num(); idx++)
		{
			SmartName::UID_Type crvUID = Skeleton->GetUIDByName(USkeleton::AnimCurveMappingName, crvmod.CurveName);

			if (crvUID != SmartName::MaxUID)
			{
				float value = 0.f;
				float lastValue = Output.Curve.Get(crvUID);

				switch (crvmod.Mode)
				{
				case EModifyCurveMode::Add:
					value = crvmod.Value + lastValue;
					break;

				case EModifyCurveMode::Replace:
					value = crvmod.Value;
					break;

				case EModifyCurveMode::Min:
					value = std::min(value, lastValue);
					break;

				case EModifyCurveMode::Max:
					value = std::max(value, lastValue);
					break;

				case EModifyCurveMode::Average:
					value = (value + lastValue) / 2.f;
					break;

				default:
					break;
				}

				Output.Curve.Set(crvUID, a * value + (1 - a) * lastValue);
			}
		}
	}
}