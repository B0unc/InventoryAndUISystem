// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Inventory/BaseInventoryComponent.h"
#include "Components/ListView.h"
#include "InventoryEntryWidget.h"
#include "../Pickup/Data/PickupItemUIObject.h"
#include "InventoryHUD.generated.h"

/**
 * 
 */
UCLASS()
class MOVEMENTSYSTEM_API UInventoryHUD : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Inventory UI")
	void RefreshInventoryUI(UBaseInventoryComponent* InventoryComponent);

	UFUNCTION(BlueprintCallable, Category = "Inventory UI")
	void OnRefreshInventoryUIUpdate();


protected:
	virtual void NativeConstruct() override;


	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UListView> InventoryListView;

private:
	TObjectPtr<UBaseInventoryComponent> CachedInventoryComp;

	UFUNCTION()
	void HandleRemovalOfPickUpItem(UPickupItemUIObject* RemovePickUpItem);
};
