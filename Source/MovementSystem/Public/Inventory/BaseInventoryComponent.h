// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseInventorySlotStruct.h"
#include "BaseInventoryComponent.generated.h"

//UI use
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdate);

// Create a delegate to up the inventory
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOVEMENTSYSTEM_API UBaseInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseInventoryComponent();

	// Issue crops up for these two pointers we probably need to use a smart pointer
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UBaseItemPickUpDataAsset* PickUpItem, int Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UBaseItemPickUpDataAsset* PickUpItem);

	//needed for the ui
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FBaseInventorySlot> GetInventorySlots() const { return InventorySlots; };

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FInventoryUpdate InventoryUpdate;

	UFUNCTION()
	bool RemoveAllItems();

	UFUNCTION()
	void PrintAllInventorySlots();

	UFUNCTION()
	void TestInventoryComponentConnection();

	//Get Functions
	int GetOccupiedInventorySlots() { return OccupiedInventorySlots; };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int MaxInventorySlots = 32;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int OccupiedInventorySlots = 0;

	// Change to a map later
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FBaseInventorySlot> InventorySlots;
		
};
