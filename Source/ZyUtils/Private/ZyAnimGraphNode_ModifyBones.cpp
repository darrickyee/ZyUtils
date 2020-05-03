// Fill out your copyright notice in the Description page of Project Settings.

#include "ZyAnimGraphNode_ModifyBones.h"
#include "AnimationGraphSchema.h"

FText UZyAnimGraphNode_ModifyBones::GetTooltipText() const
{
	return FText::FromString("Transform multiple bones in selected space.");
}

FText UZyAnimGraphNode_ModifyBones::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Modify Bones");
}

FLinearColor UZyAnimGraphNode_ModifyBones::GetNodeTitleColor() const
{
	return FLinearColor(1.0f, 0.0f, 0.15f);
}

FString UZyAnimGraphNode_ModifyBones::GetNodeCategory() const
{
	return FString(TEXT("ZyUtils"));
}

void UZyAnimGraphNode_ModifyBones::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("Pose"));
}

UZyAnimGraphNode_ModifyBones::UZyAnimGraphNode_ModifyBones(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}
