// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/BasePickUpItem.h"


void ABasePickUpItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	LoadPickUpItemMesh();
}

void ABasePickUpItem::LoadPickUpItemMesh()
{
	if (!ItemPickUpDataAsset)
	{
		WorldItemMesh->SetStaticMesh(nullptr);
		return;
	}

	if (ItemPickUpDataAsset->ItemMesh.IsNull())
	{
		return;
	}

	TObjectPtr<UStaticMesh> LoadedMesh = ItemPickUpDataAsset->ItemMesh.LoadSynchronous();
	if (LoadedMesh)
	{
		WorldItemMesh->SetStaticMesh(LoadedMesh);
	}
}

void ABasePickUpItem::ReactToTrigger_Implementation(AActor* Interactor)
{
	if (!Interactor) return;

	UBaseInventoryComponent* InventoryComp = Interactor->FindComponentByClass<UBaseInventoryComponent>();

	bool SafeToDie = false;

	if (InventoryComp)
	{
		FString DebugMessage = FString::Printf(TEXT("%s has interacted with %s"), *Interactor->GetName(), *ItemPickUpDataAsset->ItemPickUpText.ItemPickUpName.ToString());
		//GEngine->AddOnScreenDebugMessage(149, 5.0f, FColor::Green, *DebugMessage);
		SafeToDie = InventoryComp->AddItem(ItemPickUpDataAsset, ItemPickUpDataAsset->MaxStackSize);
	}
	// Make sure there is no blueprint code for this to work
	//if (SafeToDie == true)
	//{
	//	Destroy();
	//}
}
