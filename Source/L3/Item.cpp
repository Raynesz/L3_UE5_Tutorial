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
UMaterial* UItemMeshAndMaterials::EpicMaterial = nullptr;
UMaterial* UItemMeshAndMaterials::RareMaterial = nullptr;
UMaterial* UItemMeshAndMaterials::UncommonMaterial = nullptr;
UMaterial* UItemMeshAndMaterials::CommonMaterial = nullptr;
UMaterial* UItemMeshAndMaterials::PoorMaterial = nullptr;

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

    static ConstructorHelpers::FObjectFinder<UMaterial> EpicMaterialAsset(TEXT("/Game/Material/Epic.Epic"));
    if (EpicMaterialAsset.Succeeded())
    {
        EpicMaterial = EpicMaterialAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> RareMaterialAsset(TEXT("/Game/Material/Rare.Rare"));
    if (RareMaterialAsset.Succeeded())
    {
        RareMaterial = RareMaterialAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> UncommonMaterialAsset(TEXT("/Game/Material/Uncommon.Uncommon"));
    if (UncommonMaterialAsset.Succeeded())
    {
        UncommonMaterial = UncommonMaterialAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> CommonMaterialAsset(TEXT("/Game/Material/Common.Common"));
    if (CommonMaterialAsset.Succeeded())
    {
        CommonMaterial = CommonMaterialAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> PoorMaterialAsset(TEXT("/Game/Material/Poor.Poor"));
    if (PoorMaterialAsset.Succeeded())
    {
        PoorMaterial = PoorMaterialAsset.Object;
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
    else if (Quality == "Epic") {
        if (UItemMeshAndMaterials::EpicMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, UItemMeshAndMaterials::EpicMaterial);
        }
    }
    else if (Quality == "Rare") {
        if (UItemMeshAndMaterials::RareMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, UItemMeshAndMaterials::RareMaterial);
        }
    }
    else if (Quality == "Uncommon") {
        if (UItemMeshAndMaterials::UncommonMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, UItemMeshAndMaterials::UncommonMaterial);
        }
    }
    else if (Quality == "Common") {
        if (UItemMeshAndMaterials::CommonMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, UItemMeshAndMaterials::CommonMaterial);
        }
    }
    else if (Quality == "Poor") {
        if (UItemMeshAndMaterials::PoorMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, UItemMeshAndMaterials::PoorMaterial);
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
