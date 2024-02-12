// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/SCAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const USCAttributeSet* SCAttributeSet = CastChecked<USCAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(SCAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(SCAttributeSet->GetMaxHealth());
}
