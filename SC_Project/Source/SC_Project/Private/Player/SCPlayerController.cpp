// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/SCCharacter.h"

ASCPlayerController::ASCPlayerController()
{
	bReplicates = true; //responding to data updating on server and send to clients (multiplayer)
}

void ASCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(SCContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(SCContext, 0);

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

	Cast<ASCCharacter>(GetPawn<APawn>())->GetAnimInstance()->JumpToNode();
}

