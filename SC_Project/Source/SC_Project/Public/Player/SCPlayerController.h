// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SCPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class SC_PROJECT_API ASCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASCPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isMovementLocked = false;

	FVector gridSpawnPosition;
	float divisor = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AActor* GridSetUp;


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> SCContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> GridAction;

	void Move(const struct FInputActionValue& InputActionValue);
	void Jump();
	void StopJump();
	void SpawnGrid();
};
