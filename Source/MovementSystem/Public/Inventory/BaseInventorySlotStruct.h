// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Pickup/Data/BaseItemPickUpDataAsset.h"
#include "BaseInventorySlotStruct.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FBaseInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBaseItemPickUpDataAsset> PickUpItemData = nullptr;


	UPROPERTY(BlueprintReadOnly)
	int ItemInventoryQuantity = 0;

	UPROPERTY(BlueprintReadOnly)
	int StackItemLimit = 999;

	FBaseInventorySlot() {}
	FBaseInventorySlot(TObjectPtr<UBaseItemPickUpDataAsset> InPickUpItemData, int32 InQuantity) : PickUpItemData(InPickUpItemData), ItemInventoryQuantity(InQuantity) 
	{
		if (PickUpItemData)
		{
			if (PickUpItemData->bIsStackable == false)
			{
				StackItemLimit = 1;
			}
		}
	}
};
