#include "ItemMeshAndMaterials.h"

UStaticMesh* ItemMeshAndMaterials::CubeMesh = nullptr;
UStaticMesh* ItemMeshAndMaterials::SphereMesh = nullptr;
UStaticMesh* ItemMeshAndMaterials::ConeMesh = nullptr;
UMaterial* ItemMeshAndMaterials::WorldGridMaterial = nullptr;
UMaterial* ItemMeshAndMaterials::RedMaterial = nullptr;
UMaterial* ItemMeshAndMaterials::LegendaryMaterial = nullptr;
UMaterial* ItemMeshAndMaterials::EpicMaterial = nullptr;
UMaterial* ItemMeshAndMaterials::RareMaterial = nullptr;
UMaterial* ItemMeshAndMaterials::UncommonMaterial = nullptr;
UMaterial* ItemMeshAndMaterials::CommonMaterial = nullptr;
UMaterial* ItemMeshAndMaterials::PoorMaterial = nullptr;

void ItemMeshAndMaterials::Initialize()
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
