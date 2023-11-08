// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCCharacterBase.h"

ASCCharacterBase::ASCCharacterBase()
{
}

UAbilitySystemComponent* ASCCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
