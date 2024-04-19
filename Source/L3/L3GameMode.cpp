// Copyright 2024 Raynesz


#include "L3GameMode.h"
#include "ItemDatabase.h"
#include "Item.h"

void AL3GameMode::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	UItemDatabase* ItemDatabase = UItemDatabase::GetInstance();

	if (ItemDatabase)
	{
		try {
			ItemDatabase->LoadItemsFromJson();
			const TArray<FItemData>& ItemsArray = ItemDatabase->Items;

			for (const FItemData& Item : ItemsArray)
			{
				AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), FVector(0.f, 0.f, 200.f), FRotator());

				UE_LOG(LogTemp, Log, TEXT("ItemGuid: %s"), *Item.ItemGuid.ToString());
				UE_LOG(LogTemp, Warning, TEXT("ItemName: %s"), *Item.ItemName.ToString());
				UE_LOG(LogTemp, Warning, TEXT("Quality: %s"), *Item.Quality);
				UE_LOG(LogTemp, Warning, TEXT("Level: %d"), Item.Level);
				UE_LOG(LogTemp, Warning, TEXT("ItemType: %s"), *Item.ItemType);
				UE_LOG(LogTemp, Warning, TEXT("UniqueEquipped: %s"), Item.UniqueEquipped ? TEXT("True") : TEXT("False"));
				UE_LOG(LogTemp, Warning, TEXT("Mesh: %s"), *Item.Mesh);
			}
		}
		catch (const std::exception& e) {
			UE_LOG(LogTemp, Warning, TEXT("Standard library exception caught: %s"), UTF8_TO_TCHAR(e.what()));
		}
		catch (...) {
			UE_LOG(LogTemp, Warning, TEXT("Unknown exception caught"));
		}
	}
}
