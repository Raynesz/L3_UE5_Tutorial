// Copyright 2024 Raynesz


#include "Item.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"
#include "ItemMeshAndMaterials.h"
#include "ItemDatabase.h"

AItem::AItem()
{   
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent")); 
}

void AItem::SetItemProperties(FGuid Guid, FString Quality, FString Mesh)
{
    ItemGuid = Guid;

    if (Mesh == "Sphere") {
        if (ItemMeshAndMaterials::SphereMesh)
        {
            GetStaticMeshComponent()->SetStaticMesh(ItemMeshAndMaterials::SphereMesh);
        }
    }
    else if (Mesh == "Cone") {
        if (ItemMeshAndMaterials::ConeMesh)
        {
            GetStaticMeshComponent()->SetStaticMesh(ItemMeshAndMaterials::ConeMesh);
        }
    }
    else {
        if (ItemMeshAndMaterials::CubeMesh)
        {
            GetStaticMeshComponent()->SetStaticMesh(ItemMeshAndMaterials::CubeMesh);
        }
    }

    if (Quality == "Legendary") {
        if (ItemMeshAndMaterials::LegendaryMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::LegendaryMaterial);
        }
    }
    else if (Quality == "Epic") {
        if (ItemMeshAndMaterials::EpicMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::EpicMaterial);
        }
    }
    else if (Quality == "Rare") {
        if (ItemMeshAndMaterials::RareMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::RareMaterial);
        }
    }
    else if (Quality == "Uncommon") {
        if (ItemMeshAndMaterials::UncommonMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::UncommonMaterial);
        }
    }
    else if (Quality == "Common") {
        if (ItemMeshAndMaterials::CommonMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::CommonMaterial);
        }
    }
    else if (Quality == "Poor") {
        if (ItemMeshAndMaterials::PoorMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::PoorMaterial);
        }
    }
    else {
        if (ItemMeshAndMaterials::WorldGridMaterial)
        {
            GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::WorldGridMaterial);
        }
    }
}

void AItem::SetItemProperties(FGuid Guid)
{
    ItemGuid = Guid;

    for (const FItemData& Item : UItemDatabase::Items)
    {
        if (Item.ItemGuid == Guid) {
            if (Item.Mesh == "Sphere") {
                if (ItemMeshAndMaterials::SphereMesh)
                {
                    GetStaticMeshComponent()->SetStaticMesh(ItemMeshAndMaterials::SphereMesh);
                }
            }
            else if (Item.Mesh == "Cone") {
                if (ItemMeshAndMaterials::ConeMesh)
                {
                    GetStaticMeshComponent()->SetStaticMesh(ItemMeshAndMaterials::ConeMesh);
                }
            }
            else {
                if (ItemMeshAndMaterials::CubeMesh)
                {
                    GetStaticMeshComponent()->SetStaticMesh(ItemMeshAndMaterials::CubeMesh);
                }
            }

            if (Item.Quality == "Legendary") {
                if (ItemMeshAndMaterials::LegendaryMaterial)
                {
                    GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::LegendaryMaterial);
                }
            }
            else if (Item.Quality == "Epic") {
                if (ItemMeshAndMaterials::EpicMaterial)
                {
                    GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::EpicMaterial);
                }
            }
            else if (Item.Quality == "Rare") {
                if (ItemMeshAndMaterials::RareMaterial)
                {
                    GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::RareMaterial);
                }
            }
            else if (Item.Quality == "Uncommon") {
                if (ItemMeshAndMaterials::UncommonMaterial)
                {
                    GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::UncommonMaterial);
                }
            }
            else if (Item.Quality == "Common") {
                if (ItemMeshAndMaterials::CommonMaterial)
                {
                    GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::CommonMaterial);
                }
            }
            else if (Item.Quality == "Poor") {
                if (ItemMeshAndMaterials::PoorMaterial)
                {
                    GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::PoorMaterial);
                }
            }
            else {
                if (ItemMeshAndMaterials::WorldGridMaterial)
                {
                    GetStaticMeshComponent()->SetMaterial(0, ItemMeshAndMaterials::WorldGridMaterial);
                }
            }
        }
    }
}

void AItem::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));

    SetMobility(EComponentMobility::Movable);

    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SetRootComponent(CollisionComponent);

    GetStaticMeshComponent()->SetSimulatePhysics(true);
}
