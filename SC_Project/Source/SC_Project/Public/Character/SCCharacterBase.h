// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "SCCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class SC_PROJECT_API ASCCharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ASCCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
