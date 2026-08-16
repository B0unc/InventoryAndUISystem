// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HUD/ManagerHUDWidget.h"
#include "BaseCharacterHealthComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "HUD/GameplayHUD.h"
#include "HUD/HUDType.h"
#include "BasePlayerController.generated.h"

class UInputMappingContext;
class ABaseMovementCharacter;
class UInputAction;
/**
 * 
 */
UCLASS()
class MOVEMENTSYSTEM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

	// Setup Input
	virtual void SetupInputComponent() override;

protected:
	// Input Handling
	UPROPERTY(EditAnywhere, category = "Input Mapping")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Input Mapping|Actions")
	TObjectPtr<UInputAction> OpenInventoryAction;



	/*Character Class to Respawn as when destroyed*/
	UPROPERTY(EditAnywhere, Category="Character|Respawn")
	TSubclassOf<ABaseMovementCharacter> CharacterClass;

	// Assign UI
	UPROPERTY(EditDefaultsOnly, Category="HUD|Hud Class")
	TSubclassOf<UManagerHUDWidget> ManagerHUDClass;
	
	// Setup the UI



	// Hanlde Spawn
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnPawnDestroyed(AActor* DestroyedActor);

	

	virtual void BeginPlay() override;

private:
	/* Create the instance for the hud in game*/

	UPROPERTY()
	TObjectPtr<UManagerHUDWidget> ManagerHUDInstance;

	TWeakObjectPtr<UBaseCharacterHealthComponent> CachedHealthComponent;
	TWeakObjectPtr<ABaseMovementCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<UBaseInventoryComponent> CachedInventoryComponent;

	UFUNCTION()
	void InitializeHUD();

	UFUNCTION()
	void RefreshPlayerHUD();

	// Get functions for pawn components

	UFUNCTION()
	void GetPawnHealthComponent();

	UFUNCTION()
	void GetPawnInventoryComponent();

	UFUNCTION()
	void GetCurrentPawnPointer();

	UFUNCTION()
	void InitializePlayerCharacterComponents();


	UFUNCTION()
	void RefreshPlayerInventoryUI();

	UFUNCTION()
	void ExecuteOpenInventory();


	void EnableMouseControlOnHUD(bool EnableMouseHUDControl);

	void SetGameStateToPause(bool EnableGamePause);
};
