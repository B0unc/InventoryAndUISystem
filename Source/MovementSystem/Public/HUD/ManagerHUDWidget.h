// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "HUDType.h"
#include "GameplayHUD.h"
#include "InventoryHUD.h"
#include "ManagerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class MOVEMENTSYSTEM_API UManagerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Change the HUD use WidgetSwitcherHUD->SetActivateWidgetIndex or SetActiveWidget
	void SwitchHUDStates(EHUDType NewStateHUD);
	void SetHUDVisibility(bool bIsVisible);

	void ShowGamePlayHUD();
	void ShowInventoryHUD();

	UGameplayHUD* GetGameplayHUD() { return GameplayHUD; };
	UInventoryHUD* GetInventoryHUD() { return InventoryHUD; };
	EHUDType GetCurrentHUDType() const { return CurrentHUDType; };

protected:
	// Widget to switch between widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcherHUD;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGameplayHUD> GameplayHUD;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryHUD> InventoryHUD;

	EHUDType CurrentHUDType = EHUDType::GameplayUI;

	bool bCurrentHUDVisibility = true;

};
