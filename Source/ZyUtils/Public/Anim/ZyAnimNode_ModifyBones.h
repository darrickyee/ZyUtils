// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNodeBase.h"
#include "ZyAnimData.h"
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

	UPROPERTY(EditAnywhere, Category = Settings, meta = (PinShownByDefault))
	FBoneModifierArray BoneModifierArray;

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

private:
	void ModifyTransform(int32 prop, FVector value, FTransform &Target, EModifyAnimMode Mode);
};