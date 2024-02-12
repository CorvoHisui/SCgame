// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SCHUD.h"
#include "UI/Widget/SCUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ASCHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr) {
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void ASCHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_SCHub"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_SCHub"));

	//OverlayWidget = CreateWidget<USCUserWidget>(GetWorld(), OverlayWidgetClass);
	//OverlayWidget->AddToViewport();

	//InventoryWidget = CreateWidget<USCUserWidget>(GetWorld(), InventoryWidgetClass);
	//InventoryWidget->AddToViewport();

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<USCUserWidget>(widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	widget->AddToViewport();

}

