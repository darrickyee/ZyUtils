// Fill out your copyright notice in the Description page of Project Settings.

#include "ZyAnimGraphNode_OffsetBones.h"
#include "AnimationGraphSchema.h"

FText UZyAnimGraphNode_OffsetBones::GetTooltipText() const
{
	return FText::FromString("Offset multiple bones in selected space.");
}

FText UZyAnimGraphNode_OffsetBones::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Offset Bones");
}

FLinearColor UZyAnimGraphNode_OffsetBones::GetNodeTitleColor() const
{
	return FLinearColor(1.0f, 0.0f, 0.15f);
}

FString UZyAnimGraphNode_OffsetBones::GetNodeCategory() const
{
	return FString(TEXT("ZyUtils"));
}

void UZyAnimGraphNode_OffsetBones::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("Pose"));
}

UZyAnimGraphNode_OffsetBones::UZyAnimGraphNode_OffsetBones(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}
