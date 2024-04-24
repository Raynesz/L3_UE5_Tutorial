#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDatabase.h"
#include "InventoryWidget.generated.h"

class UListView;

UCLASS()
class L3_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void RefreshInventory(const TArray<FItemData>& Inventory);

private:
	UPROPERTY(meta = (BindWidget))
	UListView* ItemList;
};
