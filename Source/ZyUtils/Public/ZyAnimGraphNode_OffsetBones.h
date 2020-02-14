// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_Base.h"
#include "ZyAnimNode_OffsetBones.h"
#include "ZyAnimGraphNode_OffsetBones.generated.h"

/**
 * 
 */
UCLASS()
class ZYUTILS_API UZyAnimGraphNode_OffsetBones : public UAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = SkeletalControl)
	FZyAnimNode_OffsetBones Node;

	//~ Begin UEdGraphNode Interface.
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual FString GetNodeCategory() const override;
	virtual void CreateOutputPins() override;
	//~ End UAnimGraphNode_Base Interface

	UZyAnimGraphNode_OffsetBones(const FObjectInitializer &ObjectInitializer);
};