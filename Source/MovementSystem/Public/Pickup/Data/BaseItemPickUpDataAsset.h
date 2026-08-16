// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseItemPickUpData.h"
#include "BaseItemPickUpDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MOVEMENTSYSTEM_API UBaseItemPickUpDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EBaseItemPickUpEnum ItemPickUpType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FBaseItemPickUpStruct ItemPickUpText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TSoftObjectPtr<UStaticMesh> ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	bool bIsStackable;

	// This should be the amount of items you can find the in world for example you travel and you find a ammo bag it contains 40 round of 9mm the 40 is the MaxStackSize
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data", meta = (EditCondition = "bIsStackable", DisplayName = "Max Stack Size", ClampMin = "1", ClampMax = "254"))
	int MaxStackSize = 1;
};
