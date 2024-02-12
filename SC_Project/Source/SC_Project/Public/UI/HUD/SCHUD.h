// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SCHUD.generated.h"

class USCUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class SC_PROJECT_API ASCHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY();
	TObjectPtr<USCUserWidget> OverlayWidget;

	UPROPERTY();
	TObjectPtr<USCUserWidget> InventoryWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<USCUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USCUserWidget> InventoryWidgetClass;

	UPROPERTY();
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere);
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
