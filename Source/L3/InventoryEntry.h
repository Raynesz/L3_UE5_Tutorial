#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "InventoryEntry.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class L3_API UInventoryEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemLevel;

	UPROPERTY(meta = (BindWidget))
	UButton* DropButton;

	UFUNCTION()
	void DropItem();
};
