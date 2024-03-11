// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SCAttributeSet.h"

#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

USCAttributeSet::USCAttributeSet()
{
	InitHealth(50.0f);
	InitMaxHealth(100.0f);
	InitStamina(50.0f);
	InitMaxStamina(100.0f);
}

void USCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USCAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}

void USCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if(Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
}

void USCAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	//source = cause the effect, target = received the effect (owner of this AS)
	
	FGameplayEffectContextHandle EffectContextHandle = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* SourceAsc = EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	//Source data
	if(IsValid(SourceAsc) && SourceAsc->AbilityActorInfo.IsValid() && SourceAsc->AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* SourceAvatarActor = SourceAsc->AbilityActorInfo->AvatarActor.Get();
		AController* SourceController = SourceAsc->AbilityActorInfo->PlayerController.Get();
		if(SourceController==nullptr && SourceAvatarActor!=nullptr)
		{
			if(APawn* Pawn = Cast<APawn>(SourceAvatarActor))
			{
				SourceController = Pawn->GetController();
			}
		}
		if(SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(SourceController->GetPawn());
		}
	}
	//Add the if target data
}

void USCAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, Health, OldHealth);
}

void USCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, MaxHealth, OldMaxHealth);
}

void USCAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, Stamina, OldStamina);
}

void USCAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USCAttributeSet, MaxStamina, OldMaxStamina);
}
