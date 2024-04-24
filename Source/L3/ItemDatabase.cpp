#include "ItemDatabase.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Item.h"

TArray<FItemData> UItemDatabase::Items;

void UItemDatabase::LoadItemsFromJson()
{
    FString JsonFilePath = FPaths::ProjectContentDir() + TEXT("Data/") + TEXT("L3_ItemDB.json");

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

    for (const auto& ItemValue : JsonArray)
    {
        const TSharedPtr<FJsonObject> ItemObject = ItemValue->AsObject();
        if (ItemObject.IsValid())
        {
            FItemData ItemData;
            ItemData.ItemGuid = FGuid::NewGuid();
            ItemData.ItemName = FName(*ItemObject->GetStringField(TEXT("Name")));
            ItemData.Quality = ItemObject->GetStringField(TEXT("Quality"));
            ItemData.Level = ItemObject->GetIntegerField(TEXT("Level"));
            ItemData.ItemType = ItemObject->GetStringField(TEXT("IType"));
            ItemData.UniqueEquipped = ItemObject->GetBoolField(TEXT("UniqueEquipped"));
            ItemData.Mesh = ItemObject->GetStringField(TEXT("Mesh"));

            Items.Add(ItemData);
        }
    }
}

void UItemDatabase::ClearItemDatabase()
{
    Items.Empty();
}
