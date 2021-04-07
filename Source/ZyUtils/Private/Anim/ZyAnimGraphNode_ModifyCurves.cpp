// Fill out your copyright notice in the Description page of Project Settings.

#include "Anim/ZyAnimGraphNode_ModifyCurves.h"
#include "AnimationGraphSchema.h"

FText UZyAnimGraphNode_ModifyCurves::GetTooltipText() const
{
	return FText::FromString("Set multiple curves.");
}

FText UZyAnimGraphNode_ModifyCurves::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Modify Curves");
}

FLinearColor UZyAnimGraphNode_ModifyCurves::GetNodeTitleColor() const
{
	return FLinearColor(1.0f, 0.0f, 0.15f);
}

FString UZyAnimGraphNode_ModifyCurves::GetNodeCategory() const
{
	return FString(TEXT("ZyUtils"));
}

void UZyAnimGraphNode_ModifyCurves::CreateOutputPins()
{
	CreatePin(EGPD_Output, UAnimationGraphSchema::PC_Struct, FComponentSpacePoseLink::StaticStruct(), TEXT("Pose"));
}

UZyAnimGraphNode_ModifyCurves::UZyAnimGraphNode_ModifyCurves(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}
