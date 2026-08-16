// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemPickUpData.generated.h"

UENUM(BlueprintType)
enum class EBaseItemPickUpEnum : uint8
{
	Consumable UMETA(DisplayName = "Consumable"),
	Tool UMETA(DisplayName = "Tool")
};

USTRUCT(BlueprintType)
struct FBaseItemPickUpStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemPickUpName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemPickUpDescription;
};
