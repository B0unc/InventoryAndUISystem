// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WorldItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));
	check(WorldItemMesh != nullptr);
	RootComponent = WorldItemMesh;

	WorldItemCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PickUpCollision"));
	WorldItemCollision->SetupAttachment(RootComponent);
	WorldItemCollision->InitSphereRadius(40.0f);
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABaseItem::ReactToTrigger_Implementation(AActor* Interactor)
{
}

