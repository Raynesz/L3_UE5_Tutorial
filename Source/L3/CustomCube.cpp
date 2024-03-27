// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCube.h"

ACustomCube::ACustomCube()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomCube::Tick(float deltat)
{
	Super::Tick(deltat);
	
	FVector location = GetActorLocation();
	SetActorLocation(FVector(location.X, location.Y, location.Z + 1));
}
