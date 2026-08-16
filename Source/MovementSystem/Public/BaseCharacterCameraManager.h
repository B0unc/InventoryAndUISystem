// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "BaseCharacterCameraManager.generated.h"

/**
 * Basic FPS Camera Manager
 * Limits min/max look pitch
 * Useful for the controller
 */
UCLASS()
class MOVEMENTSYSTEM_API ABaseCharacterCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ABaseCharacterCameraManager();

	
};
