// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Item.h"
#include "Blueprint/UserWidget.h"
#include "ItemDatabase.h"
#include "InventoryWidget.h"
#include "InputMappingContext.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ItemDatabase = NewObject<UItemDatabase>(this, TEXT("ItemDatabase"));

	if (ItemDatabase)
	{
		ItemDatabase->LoadItemsFromJson();
		const TArray<FItemData>& ItemsArray = ItemDatabase->Items;

		for (const FItemData& Item : ItemsArray)
		{
			UE_LOG(LogTemp, Warning, TEXT("ItemName: %s"), *Item.ItemName.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Quality: %s"), *Item.Quality);
			UE_LOG(LogTemp, Warning, TEXT("Level: %d"), Item.Level);
			UE_LOG(LogTemp, Warning, TEXT("ItemType: %s"), *Item.ItemType);
			UE_LOG(LogTemp, Warning, TEXT("UniqueEquipped: %s"), Item.UniqueEquipped ? TEXT("True") : TEXT("False"));
			UE_LOG(LogTemp, Warning, TEXT("Mesh: %s"), *Item.Mesh);
		}
	}

	InventoryWidget = CreateWidget<UInventoryWidget>(Cast<APlayerController>(GetController()), InventoryWidgetClass);
	InteractWidget = CreateWidget(Cast<APlayerController>(GetController()), InteractWidgetClass);
	InventoryWidget->AddToViewport(0);
	InteractWidget->AddToViewport(0);
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	InteractWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AMyCharacter::HandleMove(const FInputActionValue& ActionValue)
{
	AddMovementInput(GetActorForwardVector(), ActionValue[0]);
	AddMovementInput(GetActorRightVector(), ActionValue[1]);
}

void AMyCharacter::HandleLook(const FInputActionValue& ActionValue)
{
	AddControllerYawInput(ActionValue[0]);
	AddControllerPitchInput(ActionValue[1]);
}

void AMyCharacter::HandleInteract()
{
	if (Cast<AItem>(InteractHitResult.GetActor())) {
		FItemData* Data = ItemDatabase->Items.FindByPredicate([&](const FItemData& ItemData)
			{
				return ItemData.Class == InteractHitResult.GetActor()->GetClass();
			});
		Inventory.Emplace(*Data);
		InteractHitResult.GetActor()->Destroy();
	}
}

void AMyCharacter::InteractCheck()
{
	Cast<APlayerController>(GetController())->GetPlayerViewPoint(ViewVector, ViewRotation);
	FVector VecDirection = ViewRotation.Vector() * 200.0f;
	InteractVectorEnd = ViewVector + VecDirection;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(InteractHitResult, ViewVector, InteractVectorEnd, ECollisionChannel::ECC_GameTraceChannel1, QueryParams);

	if (Cast<AItem>(InteractHitResult.GetActor())) {
		InteractWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		InteractWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AMyCharacter::ToggleInventory()
{
	if (!InventoryWidget->IsVisible()) {
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		InventoryWidget->RefreshInventory(Inventory);

		Cast<APlayerController>(GetController())->SetInputMode(FInputModeGameAndUI());
		Cast<APlayerController>(GetController())->SetCinematicMode(true, true, true);
		Cast<APlayerController>(GetController())->bShowMouseCursor = true;
	}
	else {
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

		Cast<APlayerController>(GetController())->SetInputMode(FInputModeGameOnly());
		Cast<APlayerController>(GetController())->SetCinematicMode(false, true, true);
		Cast<APlayerController>(GetController())->bShowMouseCursor = false;
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractCheck();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (MoveAction) {
			PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::HandleMove);
		}
		if (LookAction) {
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::HandleLook);
		}
		if (JumpAction) {
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
		if (InteractAction) {
			PlayerEnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::HandleInteract);
		}
		if (InventoryAction) {
			PlayerEnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &AMyCharacter::ToggleInventory);
		}
	}
}

void AMyCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = Cast<APlayerController>(GetController())->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

