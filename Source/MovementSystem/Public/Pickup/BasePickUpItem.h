// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "Data/BaseItemPickUpDataAsset.h"
#include "../Inventory/BaseInventoryComponent.h"
#include "BasePickUpItem.generated.h"


/**
 * 
 */
UCLASS()
class MOVEMENTSYSTEM_API ABasePickUpItem : public ABaseItem
{
	GENERATED_BODY()


protected:
	void LoadPickUpItemMesh();

	void OnConstruction(const FTransform& Transform);
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Asset")
	TObjectPtr<UBaseItemPickUpDataAsset> ItemPickUpDataAsset;

	void ReactToTrigger_Implementation(AActor* Interactor) override;
};
