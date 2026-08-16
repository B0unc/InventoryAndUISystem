// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "BasePlayerHUD.generated.h"

/**
 * 
 */
class UProgressBar;
UCLASS(Abstract)
class MOVEMENTSYSTEM_API UBasePlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealth(float InCurrentHealth, float InMaxHealth);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;
};
