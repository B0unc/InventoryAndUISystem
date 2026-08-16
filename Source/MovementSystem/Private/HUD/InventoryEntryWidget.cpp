// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InventoryEntryWidget.h"
//#include "../Pickup/BasePickUpItem.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UInventoryEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RemoveButton)
	{
		RemoveButton->OnClicked.AddDynamic(this, &UInventoryEntryWidget::OnRemoveButtonClicked);
	}
}

void UInventoryEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);


	CachedUIPickUpItem = Cast<UPickupItemUIObject>(ListItemObject);
	
	if (!CachedUIPickUpItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Casting the ListItemObject failed"));
		return;
	}
	else if (!CachedUIPickUpItem->PickUpItemUIDataAsset)
	{

		UE_LOG(LogTemp, Warning, TEXT("Getting the Data Asset failed"));
		return;
	}

	// Set the name & Description for the individual entry
	if (NameLabel)
	{
		NameLabel->SetText(FText::FromString(CachedUIPickUpItem->PickUpItemUIDataAsset->ItemPickUpText.ItemPickUpName.ToString()));
	}

	if (DescriptionLabel)
	{
		DescriptionLabel->SetText(FText::FromString(CachedUIPickUpItem->PickUpItemUIDataAsset->ItemPickUpText.ItemPickUpDescription.ToString()));
	}

	if (CurrentStackItemTotalUI)
	{
		FString ConvertCurrentStackSizeToString = FString::FromInt(CachedUIPickUpItem->CurrentSlotStackItemTotal);
		CurrentStackItemTotalUI->SetText(FText::FromString(ConvertCurrentStackSizeToString));
	}

	if (MaxStackItemUI)
	{
		if (CachedUIPickUpItem->PickUpItemUIDataAsset->bIsStackable == true)
		{
			FString ConvertMaxStackSizeToString = FString::FromInt(CachedUIPickUpItem->MaxSlotStackItemTotal);
			MaxStackItemUI->SetText(FText::FromString(ConvertMaxStackSizeToString));
		}
		else if(CachedUIPickUpItem->PickUpItemUIDataAsset->bIsStackable == false)
		{
			MaxStackItemUI->SetText(FText::FromString(""));
		}

	}

}

void UInventoryEntryWidget::OnRemoveButtonClicked()
{
	if (CachedUIPickUpItem)
	{
		CachedUIPickUpItem->RemoveUIPickUpItem.Broadcast(CachedUIPickUpItem);
		UE_LOG(LogTemp, Display, TEXT("Remove Button has been clicked Base Item Name: %s"), *CachedUIPickUpItem->PickUpItemUIDataAsset->ItemPickUpText.ItemPickUpName.ToString());
	}
}
