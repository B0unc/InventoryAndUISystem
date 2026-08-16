// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDType.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EHUDType : uint8
{
	GameplayUI UMETA(DisplayName = "GameplayUI"),
	InventoryUI UMETA(DisplayName = "InventoryUI"),
	InGameMenuUI UMETA(DisplayName = "InGameMenuUI")
};
