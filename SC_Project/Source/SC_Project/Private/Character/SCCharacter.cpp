// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SCCharacter.h"

#include "AbilitySystemComponent.h"
#include "Player/SCPlayerState.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Actor.h"

#include "Kismet/KismetMathLibrary.h"
#include <Player/SCPlayerController.h>
#include <Grid/GridSetUp.h>
#include "UI/HUD/SCHUD.h"

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

	if (ASCPlayerController* SCPlayerController = Cast<ASCPlayerController>(GetController())) {
		if (ASCHUD* SCHUD = Cast <ASCHUD>(SCPlayerController->GetHUD())) {
			SCHUD->InitOverlay(SCPlayerController, SCPlayerState, AbilitySystemComponent, Cast<UAttributeSet>(AttributeSet));
		}
	}

}

void ASCCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	RotateCharacter();

	if (Cast<ASCPlayerController>(GetController())->GridSetActor) {
		if (abs((UKismetMathLibrary::VSize(GetActorLocation() - FVector(0, 0, -46) - GridSpawnPoint))) > 50) {
			CenterGridToPlayer();
		}
	}

}

void ASCCharacter::RotateCharacter()
{
	if (GetMovementComponent()->Velocity.X > 0) {
		GetSprite()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	if (GetMovementComponent()->Velocity.X < 0) {
		GetSprite()->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	}
}

FVector ASCCharacter::SetGridSpawnPoint()
{
	float LocationX = GetActorLocation().X;
	float LocationY = GetActorLocation().Y;
	float LocationZ = GetActorLocation().Z;
	float reminder;
	GridSpawnPoint = UKismetMathLibrary::MakeVector(UKismetMathLibrary::FMod(LocationX, Divisor, reminder) * Divisor,
		UKismetMathLibrary::FMod(LocationY, Divisor, reminder) * Divisor,
		LocationZ - 44.0f);
	return GridSpawnPoint;
}

void ASCCharacter::CenterGridToPlayer()
{
	if (Cast<ASCPlayerController>(GetController())->GridSetActor) {
		SetGridSpawnPoint();
		Cast<ASCPlayerController>(GetController())->GridSetActor->SetActorLocation(GridSpawnPoint);
	}
}
