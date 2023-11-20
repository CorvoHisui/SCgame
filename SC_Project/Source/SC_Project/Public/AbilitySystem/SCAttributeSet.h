// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "SCAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class SC_PROJECT_API USCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USCAttributeSet();

	//UPROPERTY(ReplicatedUsing = OnRep_Health)
	//FGameplayAttributeData Health;
};
