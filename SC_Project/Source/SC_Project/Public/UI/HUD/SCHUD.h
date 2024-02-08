// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SCHUD.generated.h"

class USCUserWidget;
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

protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<USCUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USCUserWidget> InventoryWidgetClass;
};
