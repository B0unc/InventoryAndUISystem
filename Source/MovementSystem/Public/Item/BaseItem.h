// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "../Interface/InteractInterface.h"
#include "BaseItem.generated.h"

UCLASS()
class MOVEMENTSYSTEM_API ABaseItem : public AActor, public IInteractInterface 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> WorldItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<USphereComponent> WorldItemCollision;

	void ReactToTrigger_Implementation(AActor* Interactor) override;
};
