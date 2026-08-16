// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BasePlayerHUD.h"

void UBasePlayerHUD::SetHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthProgressBar)
	{
		// Switch case for Color
		// Set FillColorAndOpacity (FLinearColor)
		HealthProgressBar->SetPercent(CurrentHealth / MaxHealth);
	}
}
