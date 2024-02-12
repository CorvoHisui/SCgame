// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/SCCharacter.h"
#include "PaperZDAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include <Grid/GridSetUp.h>

ASCPlayerController::ASCPlayerController()
{
	bReplicates = true; //responding to data updating on server and send to clients (multiplayer)
}

void ASCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(SCContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) {
		Subsystem->AddMappingContext(SCContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ASCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComonent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComonent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASCPlayerController::Move);

	EnhancedInputComonent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASCPlayerController::Jump);
	EnhancedInputComonent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASCPlayerController::StopJump);

	EnhancedInputComonent->BindAction(GridAction, ETriggerEvent::Started, this, &ASCPlayerController::SpawnGrid);

}

void ASCPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		if (!isMovementLocked) {
			ControlledPawn->AddMovementInput(-FowardDirection, InputAxisVector.Y);
			ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
		}
	}
}

void ASCPlayerController::Jump()
{
	if (ASCCharacter* ControlledCharacter = GetPawn<ASCCharacter>()) {
		ControlledCharacter->GetMovementComponent()->StopMovementImmediately();
		isMovementLocked = true;

		ControlledCharacter->GetAnimInstance()->JumpToNode("airborne");
	}
}

void ASCPlayerController::StopJump()
{
	if (ASCCharacter* ControlledCharacter = GetPawn<ASCCharacter>()) {
		ControlledCharacter->StopJumping();
	}
}

void ASCPlayerController::SpawnGrid()
{
	if (ASCCharacter* ControlledCharacter = GetPawn<ASCCharacter>()) {
		if (GridSetActor) {

			GridSetActor->Destroy();
			GridSetActor = nullptr;
		}
		else {
			float reminder=0;
			
			
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;

			GridSetActor = GetWorld()->SpawnActor<AGridSetUp>(GridSetActorClass, ControlledCharacter->SetGridSpawnPoint(), Rotation, SpawnInfo);
		}
	}
}

