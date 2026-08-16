// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseCharacterHealthComponent.generated.h"
// UI Integration
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthDepleted); // Signals on Death
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, float, CurrentHealth, float, MaxHealth); // singals health change

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOVEMENTSYSTEM_API UBaseCharacterHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseCharacterHealthComponent();


	UPROPERTY(EditDefaultsOnly, Category="Health System", Meta=(ClampMin="0", ClampMax="10000"))
	float MaxHealth;

	UPROPERTY()
	float CurrentHealth;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthDepleted OnHealthDepleted;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChange OnHealthChange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	void UpdateCurrentHealth(float ImpactHealth);

	UFUNCTION()
	void SetInitCurrentHealth(float SetInitHealth);
};
