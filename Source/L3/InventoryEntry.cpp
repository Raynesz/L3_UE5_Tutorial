// Copyright 2024 Raynesz


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

	DropButton->OnClicked.Clear();
	DropButton->OnClicked.AddDynamic(this, &UInventoryEntry::DropItem);
}

void UInventoryEntry::DropItem()
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(GetOwningPlayer()->GetPawn());
	FItemData ItemData = GetListItem<UItemUIObject>()->ItemData;
	//GetWorld()->SpawnActor<AItem>(ItemData.Class, MyCharacter->InteractVectorEnd, FRotator());
	AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), MyCharacter->InteractVectorEnd, FRotator());
	//if (SpawnedItem)
	//{
	//	SpawnedItem->ItemGuid = ItemData.ItemGuid;
	//}

	MyCharacter->Inventory.Remove(ItemData);
	MyCharacter->InventoryWidget->RefreshInventory(MyCharacter->Inventory);
}
