// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridSetUp.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AGridSetUp::AGridSetUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridSetUp::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < GridX-1; i++)
	{
		for (int j = 0; j < GridY-1; j++)
		{
			FVector RelativeTransform = FVector((i * GridSize) - ((GridX - 1) * GridSize / 2), (j * GridSize) - ((GridX - 1) * GridSize / 2), 0.0f);
			
			AddComponent("MESH_Grid", false, UKismetMathLibrary::MakeTransform(RelativeTransform, FRotator(0, 0, 0), FVector(1, 1, 1)), MeshGridComponent, false);
		}
	}

	
}

