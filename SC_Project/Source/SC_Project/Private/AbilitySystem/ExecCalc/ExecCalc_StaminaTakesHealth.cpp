// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_StaminaTakesHealth.h"

#include "AbilitySystem/SCAttributeSet.h"

struct PBExecStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Stamina);

	PBExecStatics() 
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(USCAttributeSet, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(USCAttributeSet, Stamina, Target, false);
	}
};

static const PBExecStatics& ExecStatics()
{
	static PBExecStatics Statics;
	return Statics;
}

UExecCalc_StaminaTakesHealth::UExecCalc_StaminaTakesHealth()
{
	RelevantAttributesToCapture.Add(ExecStatics().HealthDef);
	RelevantAttributesToCapture.Add(ExecStatics().StaminaDef);
}

void UExecCalc_StaminaTakesHealth::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float OldStamina = 0;
	float NewStamina = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeBaseValue(ExecStatics().StaminaDef, OldStamina);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ExecStatics().StaminaDef, EvaluationParameters, NewStamina);

	if(NewStamina<0)
	{
		float HealthBase=0;
		ExecutionParams.AttemptCalculateCapturedAttributeBaseValue(ExecStatics().HealthDef, HealthBase);
		HealthBase+=NewStamina;
		FGameplayModifierEvaluatedData EvaluatedStaminaData(ExecStatics().StaminaProperty, EGameplayModOp::Override, 0);
		FGameplayModifierEvaluatedData EvaluatedHealthData(ExecStatics().HealthProperty, EGameplayModOp::Override, HealthBase);

		OutExecutionOutput.AddOutputModifier(EvaluatedStaminaData);
		OutExecutionOutput.AddOutputModifier(EvaluatedHealthData);
	}
	else
	{
		FGameplayModifierEvaluatedData EvaluatedData(ExecStatics().StaminaProperty, EGameplayModOp::Override, NewStamina);
		OutExecutionOutput.AddOutputModifier(EvaluatedData);
	}
}