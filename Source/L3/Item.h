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

    void SetItemProperties(FGuid Guid, FString Quality, FString Mesh);

protected:
    virtual void PostInitializeComponents() override;

private:
    UPROPERTY(VisibleAnywhere)
    UPrimitiveComponent* CollisionComponent;
};
