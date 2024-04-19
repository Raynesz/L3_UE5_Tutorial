// Copyright 2024 Raynesz

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Category = "Item")
class L3_API AItem : public AStaticMeshActor
{
    GENERATED_BODY()

public:
    AItem();

    FGuid ItemGuid;

protected:
    virtual void PostInitializeComponents() override;

private:
    UPROPERTY()
    UStaticMesh* CubeMesh;

    UPROPERTY()
    UMaterial* WorldGridMaterial;

    UPROPERTY(VisibleAnywhere)
    UPrimitiveComponent* CollisionComponent;
};
