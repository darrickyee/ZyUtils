// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "ZyFunctions.h"
#include "ZyAnimNode_ModifyBones.generated.h"

/**
 * 
 */

USTRUCT()
struct ZYUTILS_API FZyAnimNode_ModifyBones : public FAnimNode_Base
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Links, meta = (PinShownByDefault))
	FComponentSpacePoseLink ComponentPose;

	/** Map of bone names to transform offsets */
	UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))
	FBoneTransformMap BoneTransformMap;

	UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))
	TEnumAsByte<EBoneControlSpace> Space;

	UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))
	EModifyAnimMode Mode;

	UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))
	float Alpha;

public:
	FZyAnimNode_ModifyBones();
	// FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext &Context) override;
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext &Context) override;
	virtual void Update_AnyThread(const FAnimationUpdateContext &Context) override;
	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext &Output) override;
	// End of FAnimNode_Base interface
};