// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InventoryHUD.h"

void UInventoryHUD::NativeConstruct()
{
	Super::NativeConstruct();
	APawn* OwningPawn = GetOwningPlayerPawn();
	if (OwningPawn)
	{
		UBaseInventoryComponent* GetInventoryComponent = OwningPawn->FindComponentByClass<UBaseInventoryComponent>();
		if (GetInventoryComponent)
		{
			UE_LOG(LogTemp, Display, TEXT("Found Inventory Component"));
			CachedInventoryComp = GetInventoryComponent;
			CachedInventoryComp->InventoryUpdate.AddDynamic(this, &UInventoryHUD::OnRefreshInventoryUIUpdate);
		}
	}
}

void UInventoryHUD::RefreshInventoryUI(UBaseInventoryComponent* InventoryComponent)
{
	if (!InventoryListView)
	{
		return;
	}

	InventoryListView->ClearListItems();

	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Passed a null InventoryComponent"));
		return;
	}

	

	const TArray<FBaseInventorySlot> SlotArray = InventoryComponent->GetInventorySlots();
	for (const FBaseInventorySlot& SlotItem : SlotArray)
	{
		if (SlotItem.PickUpItemData != nullptr && SlotItem.ItemInventoryQuantity > 0)
		{
			UPickupItemUIObject* UIItemPickUpObject = NewObject<UPickupItemUIObject>(this);
			UIItemPickUpObject->PickUpItemUIDataAsset = SlotItem.PickUpItemData;
			UIItemPickUpObject->CurrentSlotStackItemTotal = SlotItem.ItemInventoryQuantity;
			UIItemPickUpObject->MaxSlotStackItemTotal = SlotItem.StackItemLimit;

			// Bind this object to the UIItemPickUp Delegate for removal
			UIItemPickUpObject->RemoveUIPickUpItem.AddDynamic(this, &UInventoryHUD::HandleRemovalOfPickUpItem);
			
			InventoryListView->AddItem(UIItemPickUpObject);
			int AddItemListViewIndex = InventoryListView->GetIndexForItem(UIItemPickUpObject);
			UE_LOG(LogTemp, Display, TEXT("ListView: Adding %s at index %d"), *UIItemPickUpObject->PickUpItemUIDataAsset->ItemPickUpText.ItemPickUpName.ToString(), AddItemListViewIndex);

		}

	}
}

void UInventoryHUD::OnRefreshInventoryUIUpdate()
{
	if (CachedInventoryComp)
	{
		RefreshInventoryUI(CachedInventoryComp);
	}
}


void UInventoryHUD::HandleRemovalOfPickUpItem(UPickupItemUIObject* RemovePickUpItem)
{
	if (RemovePickUpItem)
	{
		UE_LOG(LogTemp, Display, TEXT("Delgate worked removing item: %s"), *RemovePickUpItem->PickUpItemUIDataAsset->ItemPickUpText.ItemPickUpName.ToString());
		int RemoveItemIndex = InventoryListView->GetIndexForItem(RemovePickUpItem);
		UE_LOG(LogTemp, Display, TEXT("ListView: Removing %s at index %d"), *RemovePickUpItem->PickUpItemUIDataAsset->ItemPickUpText.ItemPickUpName.ToString(), RemoveItemIndex);
		CachedInventoryComp->RemoveItem(RemovePickUpItem->PickUpItemUIDataAsset);
	}
}

