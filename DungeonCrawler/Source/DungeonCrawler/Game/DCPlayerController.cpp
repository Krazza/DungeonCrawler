// Fill out your copyright notice in the Description page of Project Settings.


#include "DCPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "DungeonCrawlerGameMode.h"
#include "DungeonCrawler/Characters/BaseCharacterZD.h"
#include "Kismet/GameplayStatics.h"

void ADCPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (Subsystem && DefaultMappingContext)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 1);
		}
	}
}

void ADCPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PlayerCharacterZD = Cast<ABaseCharacterZD>(InPawn);
}

void ADCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(MoveUpInputAction, ETriggerEvent::Triggered, this, &ADCPlayerController::MoveUp);
		EnhancedInput->BindAction(MoveDownInputAction, ETriggerEvent::Triggered, this, &ADCPlayerController::MoveDown);
		EnhancedInput->BindAction(MoveRightInputAction, ETriggerEvent::Triggered, this, &ADCPlayerController::MoveRight);
		EnhancedInput->BindAction(MoveLeftInputAction, ETriggerEvent::Triggered, this, &ADCPlayerController::MoveLeft);
	}
}

void ADCPlayerController::MoveUp(const FInputActionValue& Value)
{
	HandleMovementInput(FIntPoint(-1, 0));//0 -1
}

void ADCPlayerController::MoveDown(const FInputActionValue& Value)
{
	HandleMovementInput(FIntPoint(1, 0));//0 1
}

void ADCPlayerController::MoveLeft(const FInputActionValue& Value)
{
	HandleMovementInput(FIntPoint(0, -1));//-1 0
}

void ADCPlayerController::MoveRight(const FInputActionValue& Value)
{
	HandleMovementInput(FIntPoint(0, 1));//1 0
}

void ADCPlayerController::HandleMovementInput(FIntPoint Direction)
{
	if(PlayerCharacterZD)
	{
		PlayerCharacterZD->Move(Direction, 1);
	}
}
