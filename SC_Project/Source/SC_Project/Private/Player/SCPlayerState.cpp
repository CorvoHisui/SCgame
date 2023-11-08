// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerState.h"

#include "AbilitySystem/SCAbilitySystemComponent.h"
#include "AbilitySystem/SCAttributeSet.h"

ASCPlayerState::ASCPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ASCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
