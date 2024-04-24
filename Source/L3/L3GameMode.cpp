#include "L3GameMode.h"
#include "ItemDatabase.h"
#include "Item.h"
#include "ItemMeshAndMaterials.h"

AL3GameMode::AL3GameMode() : AGameMode()
{
	ItemMeshAndMaterials::Initialize();
}

void AL3GameMode::BeginPlay()
{
    Super::BeginPlay();

	UItemDatabase::LoadItemsFromJson();

	for (const FItemData& Item : UItemDatabase::Items)
	{
		AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), FVector(0.f, 0.f, 200.f), FRotator());
		if (SpawnedItem) {
			SpawnedItem->SetItemProperties(Item.ItemGuid, Item.Quality, Item.Mesh);
		}
	}
}

void AL3GameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UItemDatabase::ClearItemDatabase();
}
