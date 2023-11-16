// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCCharacter.h"

#include "AbilitySystemComponent.h"
#include "Player/SCPlayerState.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Actor.h"

#include "Kismet/KismetMathLibrary.h"

ASCCharacter::ASCCharacter()
{
}

void ASCCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for server
	InitAbilityActorInfo();
}

void ASCCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init ability actor info for client
	InitAbilityActorInfo();
}

void ASCCharacter::InitAbilityActorInfo()
{
	ASCPlayerState* SCPlayerState = GetPlayerState<ASCPlayerState>();
	check(SCPlayerState);
	SCPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SCPlayerState, this);
	AbilitySystemComponent = SCPlayerState->GetAbilitySystemComponent();
	AttributeSet = SCPlayerState->GetAttributeSet();
}

void ASCCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	RotateCharacter();
}

void ASCCharacter::RotateCharacter()
{
	FHitResult Hit;
	if (GetMovementComponent()->Velocity.X > 0) {
		GetSprite()->K2_SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f), false, Hit, false);
	}
	if (GetMovementComponent()->Velocity.X < 0) {
		GetSprite()->K2_SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f), false, Hit, false);
	}
}

void ASCCharacter::SetGridSpawnPoint()
{
	float LocationX = GetActorLocation().X;
	float LocationY = GetActorLocation().Y;
	float LocationZ = GetActorLocation().Z;
	float reminder;
	GridSpawnPoint = UKismetMathLibrary::MakeVector(UKismetMathLibrary::FMod(LocationX, Divisor, reminder) * Divisor, UKismetMathLibrary::FMod(LocationY, Divisor, reminder) * Divisor, LocationZ - 44.0f);
}

void ASCCharacter::CenterGridToPlayer()
{

}

