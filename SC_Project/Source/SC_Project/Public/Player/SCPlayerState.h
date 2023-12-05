// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "SCPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class USCAttributeSet;

/**
 * 
 */
UCLASS()
class SC_PROJECT_API ASCPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ASCPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	USCAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USCAttributeSet> AttributeSet;
};
