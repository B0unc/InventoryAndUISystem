// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/InteractInterface.h"
#include "InputActionValue.h"
#include "BaseCharacterHealthComponent.h"
#include "Inventory/BaseInventoryComponent.h"
#include "Item/BaseItem.h"
#include "BasePlayerController.h"
#include "BaseMovementCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UInputComponent;
class UBaseCharacterHealthComponent;

UCLASS()
class MOVEMENTSYSTEM_API ABaseMovementCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Health System", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBaseCharacterHealthComponent> HealthComponent;


	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Inventory System", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBaseInventoryComponent> InventoryComponent;

public:
	// Sets default values for this character's properties
	ABaseMovementCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Create a new Input Mapping Context

	// Movement Actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MouseLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> DevAction;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> InteractAction;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// FPS Camera Setup
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;


	UPROPERTY(EditAnywhere, Category = Camera)
	FVector FirstPersonCameraOffset;

	UPROPERTY(EditAnywhere, Category = Camera)
	float FirstPersonFieldOfView;

	UPROPERTY(EditAnywhere, Category = Camera)
	float FirstPersonScale;

	// Skeleton Mesh Setup
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	TObjectPtr<USkeletalMeshComponent> FirstPersonMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	FVector DefaultMeshLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	FRotator DefaultMeshRotation;


	// Timer for Respawn
	FTimerHandle TriggerToRespawn;

	UFUNCTION()
	void OnRespawn();

	// Actions
	UFUNCTION()
	void PlayerDoMove(const FInputActionValue& Value);

	UFUNCTION()
	void PlayerDoAim(const FInputActionValue& Value);

	UFUNCTION()
	void DoJump();

	UFUNCTION()
	void EndJump();

	UFUNCTION()
	void StartRun();

	UFUNCTION()
	void EndRun();

	UFUNCTION()
	void DoCrouch();

	UFUNCTION()
	void EndCrouch();

	UFUNCTION()
	void DevFunction();

	float GetMaxWalkSpeed();

	UFUNCTION()
	void DoInteract();

	// Death Animation
	UPROPERTY(VisibleAnywhere, Category = Default)
	TObjectPtr<USpringArmComponent> SpringArmDeathCamera;
	
	UPROPERTY(VisibleAnywhere, Category = Default)
	TObjectPtr<UCameraComponent> DeathCamera;

	UFUNCTION()
	void HandleDeathEvent();


private:
	float BaseWalkSpeed;
	float MaxRunSpeed;

	// Setup the death animation Helper Function for HandleDeathEvent
	void ExecuteDeathAnimation();

	void InteractionCheck();
	void Interaction();


	FHitResult InteractHitResult;
	FVector ViewVector;
	FRotator ViewRotation;

 }; 