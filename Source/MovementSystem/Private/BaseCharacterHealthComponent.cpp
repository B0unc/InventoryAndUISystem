// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterHealthComponent.h"

// Sets default values for this component's properties
UBaseCharacterHealthComponent::UBaseCharacterHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	UE_LOG(LogTemp, Warning, TEXT("Initializer Health Component -> Current: % f | Max : % f"), CurrentHealth, MaxHealth);

}

void UBaseCharacterHealthComponent::SetInitCurrentHealth(float SetCurrentHealth)
{
	CurrentHealth = SetCurrentHealth;
}

// Called when the game starts
void UBaseCharacterHealthComponent::BeginPlay()
{

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay () Health Component -> Current: % f | Max : % f"), CurrentHealth, MaxHealth);
	Super::BeginPlay();



	if (CurrentHealth == 0 || MaxHealth == 0)
	{
		if (CurrentHealth == 0 && MaxHealth > 0)
		{
			GEngine->AddOnScreenDebugMessage(80, 5.0f, FColor::Red, TEXT("Current Health was too slow to get the max health value"));
		}
		else if (MaxHealth == 0)
		{

			GEngine->AddOnScreenDebugMessage(80, 5.0f, FColor::Red, TEXT("Did you set the health value in the blue print"));
		}
	}

}

float UBaseCharacterHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}


float UBaseCharacterHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

void UBaseCharacterHealthComponent::UpdateCurrentHealth(float ImpactHealth)
{
	CurrentHealth += ImpactHealth;
	
	// Makes sure we dont go below 0 else signal for death
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

	OnHealthChange.Broadcast(CurrentHealth, MaxHealth);

	if (CurrentHealth == 0.0)
	{
		OnHealthDepleted.Broadcast();
	}
	
}

