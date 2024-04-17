// Copyright 2024 Raynesz

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDatabase.generated.h"

class AItem;

USTRUCT()
struct FItemData {
	GENERATED_BODY()

	bool operator==(const FItemData& Other) {
		return ItemName == Other.ItemName;
	}

	UPROPERTY(EditDefaultsOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItem> Class;

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
class L3_API UItemDatabase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FItemData> Items;

	UFUNCTION(BlueprintCallable)
	void LoadItemsFromJson();
};
