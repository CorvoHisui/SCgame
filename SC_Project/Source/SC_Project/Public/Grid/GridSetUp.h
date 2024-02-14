// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "GridSetUp.generated.h"



UCLASS()
class SC_PROJECT_API AGridSetUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridSetUp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* MeshGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UStaticMeshComponent*> MeshGridComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float GridX = 6.0f;
	float GridY = 6.0f;
	float GridSize = 100.0f;

	float GridOffsetX = 1.f;
	float GridOffsetY = 1.0f;

};
