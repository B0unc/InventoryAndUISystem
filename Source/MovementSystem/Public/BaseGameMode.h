// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

/**
 * Camera Manager to limit the Up and Down look for character
 */
UCLASS()
class MOVEMENTSYSTEM_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

	/* Override the start play so we can add debug display on startup*/
	virtual void StartPlay() override;
	
};
