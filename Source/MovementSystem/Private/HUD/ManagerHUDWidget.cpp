// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ManagerHUDWidget.h"

void UManagerHUDWidget::SwitchHUDStates(EHUDType NewStateHUD)
{
	if (WidgetSwitcherHUD)
	{
		switch (NewStateHUD)
		{
		case EHUDType::GameplayUI:
			ShowGamePlayHUD();
			break;
		case EHUDType::InventoryUI:
			ShowInventoryHUD();
			break;
		default:
			ShowGamePlayHUD();
			UE_LOG(LogTemp, Warning, TEXT("EHUDType was not provided correctly used the deafult switch case"));
			break;
		}
	}
}

void UManagerHUDWidget::SetHUDVisibility(bool bIsVisible)
{
	if (WidgetSwitcherHUD && bIsVisible == false)
	{
		WidgetSwitcherHUD->SetVisibility(ESlateVisibility::Collapsed);
		bCurrentHUDVisibility = false;
	} 
	else if (WidgetSwitcherHUD && bIsVisible == true)
	{
		WidgetSwitcherHUD->SetVisibility(ESlateVisibility::Visible);
		bCurrentHUDVisibility = true;
	}
}

void UManagerHUDWidget::ShowGamePlayHUD()
{
	if (GameplayHUD)
	{
		WidgetSwitcherHUD->SetActiveWidget(GameplayHUD);
		CurrentHUDType = EHUDType::GameplayUI;
	}
}

void UManagerHUDWidget::ShowInventoryHUD()
{
	if (InventoryHUD)
	{
		WidgetSwitcherHUD->SetActiveWidget(InventoryHUD);
		CurrentHUDType = EHUDType::InventoryUI;
	}
}

