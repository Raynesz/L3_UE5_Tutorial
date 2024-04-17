// Copyright 2024 Raynesz

#include "ItemDatabase.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Item.h"

void UItemDatabase::LoadItemsFromJson()
{
    FString JsonFilePath = FPaths::ProjectContentDir() + TEXT("Data/") + TEXT("L3_ItemDB.json");

    UE_LOG(LogTemp, Warning, TEXT("JsonFilePath: %s"), *JsonFilePath);

    FString JsonString;
    if (!FFileHelper::LoadFileToString(JsonString, *JsonFilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load JSON file from %s"), *JsonFilePath);
        return;
    }

    TArray<TSharedPtr<FJsonValue>> JsonArray;
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);

    if (!FJsonSerializer::Deserialize(JsonReader, JsonArray))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON file"));
        return;
    }

    FString AssetPath = FPaths::ProjectContentDir() + TEXT("Blueprint/BP_Item.uasset");
    UClass* BP_ItemClass = StaticLoadClass(AItem::StaticClass(), nullptr, *AssetPath);

    for (const auto& ItemValue : JsonArray)
    {
        const TSharedPtr<FJsonObject> ItemObject = ItemValue->AsObject();
        if (ItemObject.IsValid())
        {
            FItemData ItemData;
            ItemData.ItemName = FName(*ItemObject->GetStringField(TEXT("Name")));
            ItemData.Class = TSubclassOf<AItem>(BP_ItemClass);
            ItemData.Quality = ItemObject->GetStringField(TEXT("Quality"));
            ItemData.Level = ItemObject->GetIntegerField(TEXT("Level"));
            ItemData.ItemType = ItemObject->GetStringField(TEXT("IType"));
            ItemData.UniqueEquipped = ItemObject->GetBoolField(TEXT("UniqueEquipped"));
            ItemData.Mesh = ItemObject->GetStringField(TEXT("Mesh"));

            Items.Add(ItemData);
        }
    }
}
