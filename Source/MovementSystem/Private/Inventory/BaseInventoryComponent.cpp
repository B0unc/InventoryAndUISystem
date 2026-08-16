// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/BaseInventoryComponent.h"

// Sets default values for this component's properties
UBaseInventoryComponent::UBaseInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UBaseInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InventorySlots.SetNum(MaxInventorySlots);
	
}

bool UBaseInventoryComponent::AddItem(UBaseItemPickUpDataAsset* PickUpItem, int Quantity)
{

	/*
		Check for errors with the parameters
		Iterate through our Inventory there are two possible choices we have
			- Check to see if the item is stackable
				- IS 
					- If does exist check to see if the IteminventoryQuantity is below the parameter quantity and then add it
					- If it doesn't exist create a new inventory slot and insert it into the array
				- NOT (we dont care if an existing item already exists in the array)
					- Create a new inventory slot and insert it into the array
	*/

	if (!PickUpItem || Quantity <= 0)
	{
		if (!PickUpItem && Quantity <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("PICKUPITEM is NULL and QUANTITY was 0 or LESS"));
		}
		else if (!PickUpItem)
		{
			UE_LOG(LogTemp, Warning, TEXT("PICKUPITEM has been FOUND to be NULL"));
		}
		else if (Quantity <= 0)
		{
			UE_LOG(LogTemp, Warning , TEXT("QUANTITY has been FOUND to be 0 or LESS"));
		}
		UE_LOG(LogTemp, Warning, TEXT("Something went wrong with the AddItem Function found in the inventory component the error checks passed"));
		return false;
	}
	int index = 0;

	UE_LOG(LogTemp, Display, TEXT("Attemping to ADD %s to ACTOR'S INVENTORY"), *PickUpItem->ItemPickUpText.ItemPickUpName.ToString());

	for (FBaseInventorySlot& Slot : InventorySlots)
	{
		if (Slot.PickUpItemData == PickUpItem && Slot.ItemInventoryQuantity < Slot.StackItemLimit && PickUpItem->bIsStackable == true)
		{
			UE_LOG(LogTemp, Display, TEXT("Attemping to compare %s to found INVENTORY item %s"), *PickUpItem->ItemPickUpText.ItemPickUpName.ToString(), *Slot.PickUpItemData->ItemPickUpText.ItemPickUpName.ToString());
			Slot.ItemInventoryQuantity = FMath::Min(Slot.ItemInventoryQuantity + Quantity, Slot.StackItemLimit);
			InventoryUpdate.Broadcast();
			UE_LOG(LogTemp, Display, TEXT("SUCCESSFULLY ADDED %d of %s to ACTOR'S INVENTORY with a TOTAL of %d at INDEX %d"), Quantity, *PickUpItem->ItemPickUpText.ItemPickUpName.ToString(), Slot.ItemInventoryQuantity, index);
			return true;
		}
		// Bug is going to occur here i know it
		if (Slot.PickUpItemData == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("FREE SPACE found in INVENTORY at INDEX %d"), index);
			if (OccupiedInventorySlots <= MaxInventorySlots)
			{
				InventorySlots[index] = FBaseInventorySlot(PickUpItem, FMath::Min(Quantity, Slot.StackItemLimit));
				OccupiedInventorySlots++;
				InventoryUpdate.Broadcast();
				UE_LOG(LogTemp, Display, TEXT("SUCCESSFULLY NEWLY ADDED %s to ACTOR'S INENTORY at INDEX %d"), *PickUpItem->ItemPickUpText.ItemPickUpName.ToString(), index);
				return true;
			}
			else
			{
				return false;
			}
		}
		index++;
	}

	UE_LOG(LogTemp, Warning, TEXT("FAILED to ADD %s to ACTOR'S INVENTORY"), *PickUpItem->ItemPickUpText.ItemPickUpName.ToString());
	return false;
}

// For now just remove the items
bool UBaseInventoryComponent::RemoveItem(UBaseItemPickUpDataAsset* PickUpItem)
{
	if (!PickUpItem)
	{
		return false;
	}

	UE_LOG(LogTemp, Display, TEXT("REMOVING %s from ACTOR'S INVENTORY"), *PickUpItem->ItemPickUpText.ItemPickUpName.ToString());

	for (int i = InventorySlots.Num() - 1; i >= 0; --i)
	{

		if (InventorySlots[i].PickUpItemData == PickUpItem)
		{

			UE_LOG(LogTemp, Display, TEXT("%s was found in RemoveItem at INDEX %d"), *InventorySlots[i].PickUpItemData->ItemPickUpText.ItemPickUpName.ToString(), i);
			UE_LOG(LogTemp, Display, TEXT("Attemping to compare PICK UP ITEM %s to INVENTORY item %s"), *PickUpItem->ItemPickUpText.ItemPickUpName.ToString(), *InventorySlots[i].PickUpItemData->ItemPickUpText.ItemPickUpName.ToString());
			OccupiedInventorySlots--;
			InventorySlots[i] = FBaseInventorySlot();
			InventoryUpdate.Broadcast();
			UE_LOG(LogTemp, Display, TEXT("SUCCESSFULLY REMOVED %s from ACTOR'S INVENTORY at INDEX %d"), *PickUpItem->ItemPickUpText.ItemPickUpName.ToString(), i);
			return true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("FAILED to REMOVE %s from ACTOR'S INVENTORY"), *PickUpItem->ItemPickUpText.ItemPickUpName.ToString());
	return false;
}

bool UBaseInventoryComponent::RemoveAllItems()
{
	if (!InventorySlots.IsEmpty() && OccupiedInventorySlots > 0)
	{
		for (int i = InventorySlots.Num() - 1; i >= 0; --i)
		{
			if (InventorySlots[i].PickUpItemData != nullptr)
			{
				UE_LOG(LogTemp, Display, TEXT("Attemping to remove %s"), *InventorySlots[i].PickUpItemData->ItemPickUpText.ItemPickUpName.ToString());
				OccupiedInventorySlots--;
				InventorySlots[i] = FBaseInventorySlot();
				InventoryUpdate.Broadcast();
				UE_LOG(LogTemp, Display, TEXT("SUCCESSFUL REMOVAL"));
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("Item was found to be null skipping removal"));
			}

		}
	}

	return false;
}

void UBaseInventoryComponent::PrintAllInventorySlots()
{
	int index = 253;
	int trueIndex = 0;
	for (FBaseInventorySlot& slot : InventorySlots)
	{
		if (slot.PickUpItemData != nullptr)
		{
			FString SlotArrayPrint = FString::Printf(TEXT(" %d {%s , %d} "), trueIndex ,*slot.PickUpItemData->ItemPickUpText.ItemPickUpName.ToString(), slot.ItemInventoryQuantity);
			GEngine->AddOnScreenDebugMessage(index, 3.0f, FColor::Green, *SlotArrayPrint);
		}
		else
		{
			FString SlotArrayPrint = FString::Printf(TEXT(" %d { EMPTY, EMPTY} "), trueIndex);
			GEngine->AddOnScreenDebugMessage(index, 3.0f, FColor::Red, *SlotArrayPrint);
		}
		index++;
		trueIndex++;
	}
}

void UBaseInventoryComponent::TestInventoryComponentConnection()
{
	UE_LOG(LogTemp, Display, TEXT("InventoryComponent has been created and connected"));
}
