// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ZyUtilsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ZYUTILS_API UZyUtilsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	bool GetGlobals();

private:
	bool Globals;
};
