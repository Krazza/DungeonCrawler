// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DCPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ABaseCharacterZD;
struct FInputActionValue;

UCLASS()
class DUNGEONCRAWLER_API ADCPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
private:

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveUpInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveDownInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveLeftInputAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* MoveRightInputAction;
	
	void MoveUp(const FInputActionValue& Value);
	void MoveDown(const FInputActionValue& Value);
	void MoveLeft(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void HandleMovementInput(FIntPoint Direction);
	
	UPROPERTY()
	ABaseCharacterZD* PlayerCharacterZD;
	
};
