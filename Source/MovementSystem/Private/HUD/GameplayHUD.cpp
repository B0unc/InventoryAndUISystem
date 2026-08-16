// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameplayHUD.h"

void UGameplayHUD::UpdatePlayerHealthBar(float CurrentHealth, float MaxHealth)
{

	float TotalHealthPercent = CurrentHealth / MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("Player Health Updated -> Current: %f | Max: %f"), CurrentHealth, MaxHealth);
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(TotalHealthPercent);

		UE_LOG(LogTemp, Warning, TEXT("Player Health Progress Bar: %f"), HealthProgressBar->GetPercent());
	}
}
