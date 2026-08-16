// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "../Pickup/Data/PickupItemUIObject.h"
#include "InventoryEntryWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;

UCLASS()
class MOVEMENTSYSTEM_API UInventoryEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	void OnRemoveButtonClicked();

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> NameLabel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DescriptionLabel;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> MaxStackItemUI;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentStackItemTotalUI;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> RemoveButton;

private:
	TObjectPtr<UPickupItemUIObject> CachedUIPickUpItem;
	
};
