// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class MOVEMENTSYSTEM_API UGameplayHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdatePlayerHealthBar(float CurrentHealth, float MaxHealth);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;
	
};
