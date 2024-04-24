#include "MyCharacter.h"
#include "Engine.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Item.h"
#include "Blueprint/UserWidget.h"
#include "ItemDatabase.h"
#include "InventoryWidget.h"
#include "InputMappingContext.h"
#include "L3GameMode.h"

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

	InventoryWidget = CreateWidget<UInventoryWidget>(Cast<APlayerController>(GetController()), InventoryWidgetClass);
	InteractWidget = CreateWidget(Cast<APlayerController>(GetController()), InteractWidgetClass);
	CrosshairWidget = CreateWidget(Cast<APlayerController>(GetController()), CrosshairWidgetClass);
	UIHintWidget = CreateWidget(Cast<APlayerController>(GetController()), UIHintWidgetClass);
	InteractWidget->AddToViewport(0);
	CrosshairWidget->AddToViewport(0);
	UIHintWidget->AddToViewport(0);
	InventoryWidget->AddToViewport(1);
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
	AItem* InteractedItem = Cast<AItem>(InteractHitResult.GetActor());
	if (InteractedItem) {
		FItemData* Data = UItemDatabase::Items.FindByPredicate([&](const FItemData& ItemData)
			{
				return ItemData.ItemGuid == InteractedItem->ItemGuid;
			});
		if (Data) {
			Inventory.Emplace(*Data);
			InventoryWidget->RefreshInventory(Inventory);
			InteractedItem->Destroy();
		}
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
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
		InventoryWidget->RefreshInventory(Inventory);

		Cast<APlayerController>(GetController())->SetInputMode(FInputModeGameAndUI());
		Cast<APlayerController>(GetController())->SetCinematicMode(true, true, true);
		Cast<APlayerController>(GetController())->bShowMouseCursor = true;
	}
	else {
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		CrosshairWidget->SetVisibility(ESlateVisibility::Visible);

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
		if (RestartAction) {
			PlayerEnhancedInputComponent->BindAction(RestartAction, ETriggerEvent::Started, this, &AMyCharacter::RestartGame);
		}
		if (QuitAction) {
			PlayerEnhancedInputComponent->BindAction(QuitAction, ETriggerEvent::Started, this, &AMyCharacter::QuitGame);
		}
	}
}

void AMyCharacter::RestartGame() {
	Cast<APlayerController>(GetController())->SetInputMode(FInputModeGameOnly());
	Cast<APlayerController>(GetController())->SetCinematicMode(false, true, true);
	Cast<APlayerController>(GetController())->bShowMouseCursor = false;

	AL3GameMode* CurrentGameMode = Cast<AL3GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CurrentGameMode->RestartGame();
}

void AMyCharacter::QuitGame() {
	Cast<APlayerController>(GetController())->ConsoleCommand("quit");
}

void AMyCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = Cast<APlayerController>(GetController())->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()) {
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

