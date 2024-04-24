#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CustomCube.generated.h"

UCLASS()
class L3_API ACustomCube : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ACustomCube();
	virtual void Tick(float deltat) override;
	
};
