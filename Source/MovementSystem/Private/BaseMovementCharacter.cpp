// Fill out your copyright notice in the Description page of Project Settings.  

#include "BaseMovementCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseMovementCharacter::ABaseMovementCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Setup FPS Camera Actor
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCameraComponent"));
	check(FirstPersonCameraComponent != nullptr);
	FirstPersonCameraOffset = FVector(2.8f, 5.9f, 0.0f);
	FirstPersonFieldOfView = 70.0f;
	FirstPersonScale = 0.6f;

	// Setup First Person Mesh
	FirstPersonMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonSkeletalMeshComponent"));
	check(FirstPersonMeshComponent != nullptr);
	FirstPersonMeshComponent->SetupAttachment(GetMesh());
	FirstPersonMeshComponent->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMeshComponent->SetCollisionProfileName(FName("NoCollision"));
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	// Attach, rotate, and mouse look camera
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMeshComponent, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FirstPersonCameraOffset, FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = FirstPersonFieldOfView;
	FirstPersonCameraComponent->FirstPersonScale = FirstPersonScale;

	// Set the mesh transform location and rotation
	DefaultMeshLocation = FVector(0.0f, 0.0f, -90.0f);
	DefaultMeshRotation = FRotator(0.0f, -90.0f, 0.0f);
	GetMesh()->SetRelativeLocation(DefaultMeshLocation); 
	GetMesh()->SetRelativeRotation(DefaultMeshRotation);
	

	// A subobject should be made visible in the blueprint
	HealthComponent = CreateDefaultSubobject<UBaseCharacterHealthComponent>(TEXT("HealthComponent"));
	InventoryComponent = CreateDefaultSubobject<UBaseInventoryComponent>(TEXT("InventoryComponent"));


	GetCapsuleComponent()->InitCapsuleSize(55.f, 60.f);
	GetCapsuleComponent()->SetCapsuleSize(55.0f, 96.0f);

	// Want to store the original walk speed since we are changing it for running
	BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	MaxRunSpeed = BaseWalkSpeed * 1.80;
	
	//Setup Character Movement Defaults
	GetCharacterMovement()->AirControl = .20f;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	// Spring Arm Camera Component
	SpringArmDeathCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmDeathCamera"));
	check(SpringArmDeathCamera != nullptr);
	SpringArmDeathCamera->SetupAttachment(GetMesh()); // Sticks to the Mesh at all times
	SpringArmDeathCamera->bUsePawnControlRotation = true; // Sloves the rotation issue
	FVector SpringArmDeathCamLocation = FVector(0.0f, 0.0f, 90.0f);
	SpringArmDeathCamera->SetRelativeLocation(SpringArmDeathCamLocation);

	//Death Cam
	DeathCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DeathCamera"));
	check(DeathCamera != nullptr);
	DeathCamera->SetupAttachment(SpringArmDeathCamera);
	FVector DeathCamLocation = FVector(-10.0f, 0.0f, 240.0f);
	FRotator DeathCamRotation = FRotator(-40.0f, 0.0f, 0.0f);
	DeathCamera->SetRelativeLocation(DeathCamLocation);
	DeathCamera->SetRelativeLocationAndRotation(DeathCamLocation, DeathCamRotation);


	UE_LOG(LogTemp, Warning, TEXT("Initiaizer in Character: Health Component -> Current: % f | Max : % f"), HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());

}

void ABaseMovementCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	FirstPersonMeshComponent->SetOnlyOwnerSee(true);

	// Third person
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->CastShadow = true;
	GetMesh()->bCastHiddenShadow = true;

	// Watch for the Death Event
	HealthComponent->OnHealthDepleted.AddDynamic(this, &ABaseMovementCharacter::HandleDeathEvent);

}

void ABaseMovementCharacter::PostInitializeComponents()
{
	HealthComponent->SetInitCurrentHealth(HealthComponent->GetMaxHealth());
	Super::PostInitializeComponents();
}

// Called every frame
void ABaseMovementCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InteractionCheck();
	if (GEngine != nullptr && IsPlayerControlled())
	{
		FString CapsuleStandingHeight = FString::Printf(TEXT("InHalfHeight: %.1f\nVeolicty: %0.3f\nMaxWalkSpeed: %0.2f\nPawn's Location in the World: (%0.2f,%0.2f,%0.2f)\n"),
			GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), GetVelocity().Size(), GetMaxWalkSpeed(), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
		GEngine->AddOnScreenDebugMessage(3, .1f, FColor::Cyan, *CapsuleStandingHeight);
	}

}

void ABaseMovementCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

// Called to bind functionality to input
void ABaseMovementCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseMovementCharacter::PlayerDoMove);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABaseMovementCharacter::DoJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABaseMovementCharacter::EndJump);

		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ABaseMovementCharacter::PlayerDoAim);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ABaseMovementCharacter::StartRun);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ABaseMovementCharacter::EndRun);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ABaseMovementCharacter::DoCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ABaseMovementCharacter::EndCrouch);

		/* Dev input make sure to take this out (5/8) we are testing health so take damage*/
		EnhancedInputComponent->BindAction(DevAction, ETriggerEvent::Triggered, this, &ABaseMovementCharacter::DevFunction);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABaseMovementCharacter::Interaction);
	}

}

void ABaseMovementCharacter::PlayerDoMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementVector.X);

		const FVector Foward = GetActorForwardVector();
		AddMovementInput(Foward, MovementVector.Y);
	}
}

void ABaseMovementCharacter::DoJump()
{
	Super::Jump();
}

void ABaseMovementCharacter::EndJump()
{
	Super::StopJumping();
}

void ABaseMovementCharacter::PlayerDoAim(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void ABaseMovementCharacter::StartRun()
{

	GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
}

void ABaseMovementCharacter::EndRun()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}

void ABaseMovementCharacter::DoCrouch()
{
	InventoryComponent->RemoveAllItems();
	Super::Crouch();
}

void ABaseMovementCharacter::EndCrouch()
{
	Super::UnCrouch();
}

float ABaseMovementCharacter::GetMaxWalkSpeed()
{
	return GetCharacterMovement()->MaxWalkSpeed;
}

void ABaseMovementCharacter::DoInteract()
{
}


// Dev Function

void ABaseMovementCharacter::DevFunction()
{
	HealthComponent->UpdateCurrentHealth(-10.0f);
	FString HealthMessageDebug = FString::Printf(TEXT("Current Health: %0.2f\nMax Health:%0.2f"),HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());
	GEngine->AddOnScreenDebugMessage(6, 5.0f, FColor::Cyan, *HealthMessageDebug);
	InventoryComponent->PrintAllInventorySlots();
}


void ABaseMovementCharacter::HandleDeathEvent()
{

	FString DeathMessageDebug = FString::Printf(TEXT("YOU DIED"));
	GEngine->AddOnScreenDebugMessage(10, 5.0f, FColor::Red, *DeathMessageDebug);

	
	GetCharacterMovement()->StopMovementImmediately();
	DisableInput(nullptr);
	ExecuteDeathAnimation();

	// Respawn
	GetWorld()->GetTimerManager().SetTimer(TriggerToRespawn, this, &ABaseMovementCharacter::OnRespawn, 5.0f ,false);
}

void ABaseMovementCharacter::ExecuteDeathAnimation()
{
	FirstPersonCameraComponent->Deactivate();
	DeathCamera->Activate();

	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
}

void ABaseMovementCharacter::OnRespawn()
{
	Destroy();
}


void ABaseMovementCharacter::InteractionCheck()
{
	Cast<APlayerController>(GetController())->GetPlayerViewPoint(ViewVector, ViewRotation);
	FVector VecDirection = ViewRotation.Vector() * 1000.f;
	FVector InteractEnd = ViewVector + VecDirection;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(InteractHitResult, ViewVector, InteractEnd, ECollisionChannel::ECC_GameTraceChannel1, QueryParams);
	DrawDebugLine(GetWorld(), ViewVector, InteractEnd, InteractHitResult.bBlockingHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 1.0f);
}

void ABaseMovementCharacter::Interaction()
{

	TObjectPtr<ABaseItem> HitActor = Cast<ABaseItem>(InteractHitResult.GetActor());
	if (HitActor && HitActor->Implements<UInteractInterface>())
	{
		UE_LOG(LogTemp, Log, TEXT("Interact Button has been pressed"));
		IInteractInterface::Execute_ReactToTrigger(HitActor, this);
	}
}
