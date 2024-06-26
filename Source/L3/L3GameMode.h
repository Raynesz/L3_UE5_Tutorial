#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "L3GameMode.generated.h"

UCLASS()
class L3_API AL3GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AL3GameMode();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
