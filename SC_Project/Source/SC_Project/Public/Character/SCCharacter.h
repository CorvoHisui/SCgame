// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SCCharacterBase.h"
#include "SCCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SC_PROJECT_API ASCCharacter : public ASCCharacterBase
{
	GENERATED_BODY()
public:
	ASCCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilityActorInfo();
	virtual void Tick(float DeltaSeconds);
	void RotateCharacter();

	float Divisor = 100.0f;
	FVector GridSpawnPoint;
	void SetGridSpawnPoint();
	
	void CenterGridToPlayer();
};
