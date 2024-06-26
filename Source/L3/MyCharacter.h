#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemDatabase.h"
#include "InputActionValue.h"
#include "MyCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UInventoryWidget;

UCLASS()
class L3_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InventoryAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* RestartAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* QuitAction;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> InteractWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CrosshairWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> UIHintWidgetClass;

	UPROPERTY()
	UInventoryWidget* InventoryWidget;

	UPROPERTY()
	UUserWidget* InteractWidget;

	UPROPERTY()
	UUserWidget* UIHintWidget;

	UPROPERTY()
	UUserWidget* CrosshairWidget;

	UItemDatabase* ItemDatabase;

	FVector InteractVectorEnd;

	TArray<FItemData> Inventory;

protected:
	virtual void BeginPlay() override;

private:
	void HandleMove(const FInputActionValue& ActionValue);
	void HandleLook(const FInputActionValue& ActionValue);

	void HandleInteract();
	void InteractCheck();
	void ToggleInventory();

	void RestartGame();
	void QuitGame();

	FHitResult InteractHitResult;
	FVector ViewVector;
	FRotator ViewRotation;
};
