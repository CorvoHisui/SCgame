// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SCEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/SCAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
ASCEffectActor::ASCEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASCEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASCEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent *TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if(TargetASC == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
}



