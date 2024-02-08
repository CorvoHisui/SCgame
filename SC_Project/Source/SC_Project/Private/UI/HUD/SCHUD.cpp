// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SCHUD.h"

#include "UI/Widget/SCUserWidget.h"

void ASCHUD::BeginPlay()
{
	Super::BeginPlay();

	OverlayWidget = CreateWidget<USCUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->AddToViewport();

	InventoryWidget = CreateWidget<USCUserWidget>(GetWorld(), InventoryWidgetClass);
	InventoryWidget->AddToViewport();

}
