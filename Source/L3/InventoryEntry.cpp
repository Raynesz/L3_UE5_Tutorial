#include "InventoryEntry.h"
#include "ItemDatabase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "MyCharacter.h"
#include "InventoryWidget.h"
#include "Item.h"

void UInventoryEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UItemUIObject* UIItem = Cast<UItemUIObject>(ListItemObject);
	ItemName->SetText(FText::FromString(UIItem->ItemData.ItemName.ToString()));

	FLinearColor TextColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (UIItem->ItemData.Quality == "Legendary")
	{
		TextColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
	}
	else if (UIItem->ItemData.Quality == "Epic")
	{
		TextColor = FLinearColor(0.64f, 0.2f, 0.93f, 1.0f);
	}
	else if (UIItem->ItemData.Quality == "Rare")
	{
		TextColor = FLinearColor(0.0f, 0.44f, 0.87f, 1.0f);
	}
	else if (UIItem->ItemData.Quality == "Uncommon")
	{
		TextColor = FLinearColor(0.12f, 0.7f, 0.0f, 1.0f);
	}
	else if (UIItem->ItemData.Quality == "Poor")
	{
		TextColor = FLinearColor(0.5f, 0.5f, 0.5f, 1.0f);
	}

	ItemName->SetColorAndOpacity(TextColor);

	ItemLevel->SetText(FText::FromString(FString::Printf(TEXT("[%d]"), UIItem->ItemData.Level)));
	ItemLevel->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));

	DropButton->OnClicked.Clear();
	DropButton->OnClicked.AddDynamic(this, &UInventoryEntry::DropItem);
}

void UInventoryEntry::DropItem()
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(GetOwningPlayer()->GetPawn());
	FItemData ItemData = GetListItem<UItemUIObject>()->ItemData;
	AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), MyCharacter->InteractVectorEnd, FRotator());
	if (SpawnedItem)
	{
		SpawnedItem->SetItemProperties(ItemData.ItemGuid);
	}

	MyCharacter->Inventory.Remove(ItemData);
	MyCharacter->InventoryWidget->RefreshInventory(MyCharacter->Inventory);
}
