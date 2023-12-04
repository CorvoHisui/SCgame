// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/GridSetUp.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AGridSetUp::AGridSetUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* GridRoot = CreateDefaultSubobject<USceneComponent>(FName("GridRoot"));
	SetRootComponent(GridRoot);

	for (int i = 0; i < GridX - 1; i++)
	{
		for (int j = 0; j < GridY - 1; j++)
		{
			FVector RelativeTransform = FVector(((i * GridSize) - ((GridX - 1) * GridSize / 2)) - GridOffsetX, ((j * GridSize) - ((GridX - 1) * GridSize / 2)) - GridOffsetY, 0.0f);

			FString TileName = TEXT("Tile" + FString::FromInt(i) + FString::FromInt(j));
			UStaticMeshComponent* Tile = CreateDefaultSubobject<UStaticMeshComponent>(FName(*TileName));
			Tile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			Tile->SetupAttachment(RootComponent);
			Tile->AddRelativeLocation(RelativeTransform);
			Tile->SetStaticMesh(MeshGrid);

			MeshGridComp.Add(Tile);
		}
	}
	
}


// Called when the game starts or when spawned
void AGridSetUp::BeginPlay()
{
	Super::BeginPlay();
}

