// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperZDCharacter.h"
#include "SCCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class USCAttributeSet;

/**
 * 
 */
UCLASS()
class SC_PROJECT_API ASCCharacterBase : public APaperZDCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ASCCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	USCAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Apllied Efects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<USCAttributeSet> AttributeSet;
};
