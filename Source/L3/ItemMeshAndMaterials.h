// Copyright 2024 Raynesz

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class L3_API ItemMeshAndMaterials
{
public:
    static void Initialize();

    UPROPERTY()
    static UStaticMesh* CubeMesh;

    UPROPERTY()
    static UStaticMesh* SphereMesh;

    UPROPERTY()
    static UStaticMesh* ConeMesh;

    UPROPERTY()
    static UMaterial* WorldGridMaterial;

    UPROPERTY()
    static UMaterial* RedMaterial;

    UPROPERTY()
    static UMaterial* LegendaryMaterial;

    UPROPERTY()
    static UMaterial* EpicMaterial;

    UPROPERTY()
    static UMaterial* RareMaterial;

    UPROPERTY()
    static UMaterial* UncommonMaterial;

    UPROPERTY()
    static UMaterial* CommonMaterial;

    UPROPERTY()
    static UMaterial* PoorMaterial;
};
