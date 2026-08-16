// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"

void ABaseGameMode::StartPlay() {

	// Call the start play function from parent so we can override
	Super::StartPlay();

	// Make sure the Engine is running
	check(GEngine != nullptr);

	// Add Debug message
}
