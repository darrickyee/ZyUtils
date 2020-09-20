// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "ZyFunctions.h"
#include "ZyAnimNode_ModifyCurves.generated.h"

/**
 * 
 */

USTRUCT()
struct ZYUTILS_API FZyAnimNode_ModifyCurves : public FAnimNode_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Links, meta = (PinShownByDefault))
	FComponentSpacePoseLink ComponentPose;

	UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))
	FCurveModifierArray CurveModifierArray;

	UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))
	float Alpha;

public:
	FZyAnimNode_ModifyCurves();
	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext &Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext &Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext &Context) override;
	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext &Output) override;
	// End of FAnimNode_Base interface
};