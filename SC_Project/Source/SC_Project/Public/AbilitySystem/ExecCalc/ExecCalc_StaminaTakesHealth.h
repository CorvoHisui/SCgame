// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_StaminaTakesHealth.generated.h"

/**
 * 
 */
UCLASS()
class SC_PROJECT_API UExecCalc_StaminaTakesHealth : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecCalc_StaminaTakesHealth();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
