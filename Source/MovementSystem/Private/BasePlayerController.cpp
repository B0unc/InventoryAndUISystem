// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"
#include "BaseCharacterCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "BaseMovementCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

ABasePlayerController::ABasePlayerController() {
	// Override Player Camera Manager
	PlayerCameraManagerClass = ABaseCharacterCameraManager::StaticClass();

}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(OpenInventoryAction, ETriggerEvent::Started, this, &ABasePlayerController::ExecuteOpenInventory);

	}
}


// Called when the game starts or when spawned
void ABasePlayerController::BeginPlay()
{

	UE_LOG(LogTemp, Warning, TEXT("Controller: Before the BeginPlay()"));
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Controller: After the BeginPlay()"));
	check(GEngine != nullptr); // If somthing crashes Make sure to use this line
	if (IsLocalPlayerController())// Always verify anything in life
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}

		if (ManagerHUDClass)
		{
			ManagerHUDInstance = CreateWidget<UManagerHUDWidget>(this, ManagerHUDClass);
			UE_LOG(LogTemp, Warning, TEXT("Created ManagerHUDInstance"));
			UE_LOG(LogTemp, Warning, TEXT("After Created ManagerHUDInstance"));
			ManagerHUDInstance->AddToViewport();
			ManagerHUDInstance->SwitchHUDStates(EHUDType::GameplayUI);
			InitializeHUD(); // Need for begin play

		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Start play"));

}

void ABasePlayerController::RefreshPlayerHUD()
{

}

void ABasePlayerController::InitializeHUD()
{
	if (!ManagerHUDInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ManagerHUDInstance not availbe"));
		return;
	}

//	ABaseMovementCharacter* MyChar = Cast<ABaseMovementCharacter>(GetPawn());
//	if (MyChar)
//	{
//		HealthComp = MyChar->FindComponentByClass<UBaseCharacterHealthComponent>();
//		UGameplayHUD* GameplayUI = ManagerHUDInstance->GetGameplayHUD();
//
//		if (HealthComp.IsValid() && GameplayUI)
//		{
//			HealthComp->OnHealthChange.AddDynamic(GameplayUI, &UGameplayHUD::UpdatePlayerHealthBar);
//			UE_LOG(LogTemp, Log, TEXT("Added binding to the health change"));
//			UE_LOG(LogTemp, Warning, TEXT("InitializeHUD After Binding: Health Component -> Current: % f | Max : % f"), HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth());
//
//			GameplayUI->UpdatePlayerHealthBar(HealthComp->GetCurrentHealth(), HealthComp->GetMaxHealth());
//			UE_LOG(LogTemp, Log, TEXT("Updated Health Bar"));
//		}
//	}

	ManagerHUDInstance->SetHUDVisibility(true);

	TObjectPtr<UGameplayHUD> GameplayUI = ManagerHUDInstance->GetGameplayHUD();
	if (CachedHealthComponent.IsValid() && GameplayUI)
	{
			CachedHealthComponent->OnHealthChange.AddDynamic(GameplayUI, &UGameplayHUD::UpdatePlayerHealthBar);
			UE_LOG(LogTemp, Log, TEXT("Added binding to the health change"));
			UE_LOG(LogTemp, Warning, TEXT("InitializeHUD After Binding: Health Component -> Current: % f | Max : % f"), CachedHealthComponent->GetCurrentHealth(), CachedHealthComponent->GetMaxHealth());

			GameplayUI->UpdatePlayerHealthBar(CachedHealthComponent->GetCurrentHealth(), CachedHealthComponent->GetMaxHealth());
			UE_LOG(LogTemp, Log, TEXT("Updated Health Bar"));
			if (ManagerHUDInstance->GetCurrentHUDType() != EHUDType::GameplayUI)
			{
				ManagerHUDInstance->SwitchHUDStates(EHUDType::GameplayUI);
			}

	}
}

// Setup the object ptr to the health component
void ABasePlayerController::GetPawnHealthComponent()
{
	ABaseMovementCharacter* MyChar = Cast<ABaseMovementCharacter>(GetPawn());
	if (MyChar)
	{
		TObjectPtr<UBaseCharacterHealthComponent> ValidateHealthComponent = MyChar->FindComponentByClass<UBaseCharacterHealthComponent>();
		if (ValidateHealthComponent)
		{
			CachedHealthComponent = ValidateHealthComponent;
		}
	}
}

void ABasePlayerController::GetPawnInventoryComponent()
{
	ABaseMovementCharacter* MyChar = Cast<ABaseMovementCharacter>(GetPawn());
	if (MyChar)
	{
		TObjectPtr<UBaseInventoryComponent> ValidateInventoryComponent = MyChar->FindComponentByClass<UBaseInventoryComponent>();
		if (ValidateInventoryComponent)
		{
			CachedInventoryComponent = ValidateInventoryComponent;
		}
	}
}

void ABasePlayerController::GetCurrentPawnPointer()
{
	ABaseMovementCharacter* MyChar = Cast<ABaseMovementCharacter>(GetPawn());
	if (MyChar)
	{
		CachedPlayerCharacter = MyChar;
	}
}

void ABasePlayerController::InitializePlayerCharacterComponents()
{
	GetPawnHealthComponent();
	GetPawnInventoryComponent();
}

void ABasePlayerController::ExecuteOpenInventory()
{
	if (ManagerHUDInstance)
	{
		// Open the Inventory
		if (ManagerHUDInstance->GetCurrentHUDType() != EHUDType::InventoryUI)
		{
			ManagerHUDInstance->SwitchHUDStates(EHUDType::InventoryUI);
			RefreshPlayerInventoryUI();
			EnableMouseControlOnHUD(true);
			UE_LOG(LogTemp, Warning, TEXT("Inventory Open Action has been pressed"));
		}
		// Close the inventory based on the same input
		else if(ManagerHUDInstance->GetCurrentHUDType() == EHUDType::InventoryUI)
		{
			ManagerHUDInstance->SwitchHUDStates(EHUDType::GameplayUI);
			EnableMouseControlOnHUD(false);
			UE_LOG(LogTemp, Warning, TEXT("Inventory already open"));
		}
	}
}

void ABasePlayerController::EnableMouseControlOnHUD(bool EnableMouseHUDControl)
{
	if (EnableMouseHUDControl)
	{
		// 3. SHOW MOUSE: Set up UI interaction focus
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;

		// Route input to the UI first, but allow camera/movement if unhandled (or use FInputModeUIOnly)
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		UE_LOG(LogTemp, Display, TEXT("Mouse Enable and Mouse cursor not locked to viewport"));
	}
	else if (!EnableMouseHUDControl)
	{

		bShowMouseCursor = false;
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
		UE_LOG(LogTemp,Display, TEXT("Mouse Disable and Input mode has returned back to game only"))
	}
}


void ABasePlayerController::RefreshPlayerInventoryUI()
{
	if (CachedInventoryComponent.IsValid())
	{
		if (UInventoryHUD* InventoryHUD = ManagerHUDInstance->GetInventoryHUD())
		{
			UBaseInventoryComponent* InventoryComponentParameter = CachedInventoryComponent.Get();
			InventoryHUD->RefreshInventoryUI(InventoryComponentParameter);
		}
	}
}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	InitializePlayerCharacterComponents();
	InitializeHUD();
	//RefreshPlayerHUD();
	//Sub to the OnDestroyed delegate
	InPawn->OnDestroyed.AddDynamic(this, &ABasePlayerController::OnPawnDestroyed);
	UE_LOG(LogTemp, Warning, TEXT("Taking Possession"));
}

void ABasePlayerController::OnPawnDestroyed(AActor* DestroyedActor)
{
	if (ManagerHUDInstance)
	{
		ManagerHUDInstance->SetHUDVisibility(false);
	}
	CachedHealthComponent.Reset();
	TArray<AActor*> ActorSpawnList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), ActorSpawnList);

	if (ActorSpawnList.Num() > 0)
	{

		AActor* SpawnLocationStart = ActorSpawnList[FMath::RandRange(0, ActorSpawnList.Num() - 1)];
		FTransform SpawnTransform = SpawnLocationStart->GetActorTransform();

		if (ABaseMovementCharacter* RespawnedCharacter = GetWorld()->SpawnActor<ABaseMovementCharacter>(CharacterClass, SpawnTransform))
		{
			Possess(RespawnedCharacter);

		}
		else
		{

			GEngine->AddOnScreenDebugMessage(31, 15.0f, FColor::Yellow, TEXT("Did you set the respawn Character in the controller?"));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Pawn is being Destroyed"));
}



