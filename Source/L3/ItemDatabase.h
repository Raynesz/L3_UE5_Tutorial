#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDatabase.generated.h"

class AItem;

USTRUCT(BlueprintType)
struct FItemData {
	GENERATED_BODY()

	bool operator==(const FItemData& Other) {
		return ItemName == Other.ItemName;
	}

	FItemData()
		: Level(0), UniqueEquipped(false)
	{
	}

	FGuid ItemGuid;

	UPROPERTY(EditDefaultsOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly)
	FString Quality;

	UPROPERTY(EditDefaultsOnly)
	int32 Level;

	UPROPERTY(EditDefaultsOnly)
	FString ItemType;

	UPROPERTY(EditDefaultsOnly)
	bool UniqueEquipped;

	UPROPERTY(EditDefaultsOnly)
	FString Mesh;
};

UCLASS()
class UItemUIObject : public UObject {
	GENERATED_BODY()

public:
	FItemData ItemData;
};

UCLASS()
class L3_API UItemDatabase : public UObject
{
	GENERATED_BODY()

public:
	static TArray<FItemData> Items;

	UFUNCTION()
	static void LoadItemsFromJson();

	UFUNCTION()
	static void ClearItemDatabase();
};
