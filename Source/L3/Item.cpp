// Copyright 2024 Raynesz


#include "Item.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"

AItem::AItem()
{
    SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        CubeMesh = CubeMeshAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> WorldGridMaterialAsset(TEXT("/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial"));
    if (WorldGridMaterialAsset.Succeeded())
    {
        WorldGridMaterial = WorldGridMaterialAsset.Object;
    }

    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent")); 
}

void AItem::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (CubeMesh)
    {
        GetStaticMeshComponent()->SetStaticMesh(CubeMesh);
    }

    if (WorldGridMaterial)
    {
        GetStaticMeshComponent()->SetMaterial(0, WorldGridMaterial);
    }

    SetMobility(EComponentMobility::Movable);

    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Enable physics collision detection
    SetRootComponent(CollisionComponent);

    GetStaticMeshComponent()->SetSimulatePhysics(true);
}
