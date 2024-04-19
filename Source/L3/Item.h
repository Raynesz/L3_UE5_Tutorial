// Copyright 2024 Raynesz

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class L3_API AItem : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	FGuid ItemGuid;
};
