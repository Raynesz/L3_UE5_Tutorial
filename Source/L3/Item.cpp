// Copyright 2024 Raynesz


#include "Item.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"
#include "ItemDatabase.h"

UStaticMesh* UItemMeshAndMaterials::CubeMesh = nullptr;
UStaticMesh* UItemMeshAndMaterials::SphereMesh = nullptr;
UStaticMesh* UItemMeshAndMaterials::ConeMesh = nullptr;
UMaterial* UItemMeshAndMaterials::WorldGridMaterial = nullptr;
UMaterial* UItemMeshAndMaterials::RedMaterial = nullptr;
UMaterial* UItemMeshAndMaterials::LegendaryMaterial = nullptr;

void UItemMeshAndMaterials::Initialize()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        CubeMesh = CubeMeshAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMeshAsset.Succeeded())
    {
        SphereMesh = SphereMeshAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeMeshAsset(TEXT("/Engine/BasicShapes/Cone.Cone"));
    if (ConeMeshAsset.Succeeded())
    {
        ConeMesh = ConeMeshAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> WorldGridMaterialAsset(TEXT("/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial"));
    if (WorldGridMaterialAsset.Succeeded())
    {
        WorldGridMaterial = WorldGridMaterialAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> RedMaterialAsset(TEXT("/Engine/red_001.red_001"));
    if (RedMaterialAsset.Succeeded())
    {
        RedMaterial = RedMaterialAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> LegendaryMaterialAsset(TEXT("/Game/Material/Legendary.Legendary"));
    if (LegendaryMaterialAsset.Succeeded())
    {
        LegendaryMaterial = LegendaryMaterialAsset.Object;
    }
}

AItem::AItem()
{   
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent")); 
}

void AItem::SetItemProperties(FGuid Guid, FString Quality, FString Mesh)
{
    ItemGuid = Guid;

    if (Mesh == "Sphere") {
        if (UItemMeshAndMaterials::SphereMesh)
        {
            GetStaticMeshComponent()->SetStaticMesh(UItemMeshAndMaterials::SphereMesh);
        }
    }
    else if (Mesh == "Pyramid") {
        if (UItemMeshAndMaterials::ConeMesh)
        {
            GetStaticMeshComponent()->SetStaticMesh(UItemMeshAndMaterials::ConeMesh);
        }
    }
    else {
        if (UItemMeshAndMaterials::CubeMesh)
        {
            GetStaticMeshComponent()->SetStaticMesh(UItemMeshAndMaterials::CubeMesh);
        }
    }

    if (Quality == "Legendary") {
        if (UItemMeshAndMaterials::LegendaryMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, UItemMeshAndMaterials::LegendaryMaterial);
        }
    }
    else {
        if (UItemMeshAndMaterials::WorldGridMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, UItemMeshAndMaterials::WorldGridMaterial);
        }
    }
}

void AItem::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));

    SetMobility(EComponentMobility::Movable);

    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Enable physics collision detection
    SetRootComponent(CollisionComponent);

    GetStaticMeshComponent()->SetSimulatePhysics(true);
}
