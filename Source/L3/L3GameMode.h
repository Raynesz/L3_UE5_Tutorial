// Copyright 2024 Raynesz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "L3GameMode.generated.h"

/**
 * 
 */
UCLASS()
class L3_API AL3GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
};
