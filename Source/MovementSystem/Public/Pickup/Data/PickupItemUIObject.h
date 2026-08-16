// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseItemPickUpData.h"
#include "BaseItemPickUpDataAsset.h"
#include "PickupItemUIObject.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoveItemRequest, UPickupItemUIObject*, RemoveUIPickUpItem); // singals item removal
UCLASS()
class MOVEMENTSYSTEM_API UPickupItemUIObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item UI")
	TObjectPtr<UBaseItemPickUpDataAsset> PickUpItemUIDataAsset; // Change this to Data Asset

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item UI")
	int CurrentSlotStackItemTotal;


	UPROPERTY(BlueprintReadOnly, Category = "Inventory Item UI")
	int MaxSlotStackItemTotal;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Item UI")
	FOnRemoveItemRequest RemoveUIPickUpItem;
	
};
