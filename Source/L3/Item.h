// Copyright 2024 Raynesz

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Item.generated.h"

/**
 * 
 */

class L3_API UItemMeshAndMaterials : public UObject
{
public:
    static void Initialize();

    UPROPERTY()
    static UStaticMesh* CubeMesh;

    UPROPERTY()
    static UStaticMesh* SphereMesh;

    UPROPERTY()
    static UStaticMesh* ConeMesh;

    UPROPERTY()
    static UMaterial* WorldGridMaterial;

    UPROPERTY()
    static UMaterial* RedMaterial;

    UPROPERTY()
    static UMaterial* LegendaryMaterial;
};

UCLASS(BlueprintType, Blueprintable, Category = "Item")
class L3_API AItem : public AStaticMeshActor
{
    GENERATED_BODY()

public:
    AItem();

    FGuid ItemGuid;

    void SetItemProperties(FGuid Guid, FString Quality, FString Mesh);

protected:
    virtual void PostInitializeComponents() override;

private:
    UPROPERTY(VisibleAnywhere)
    UPrimitiveComponent* CollisionComponent;
};
