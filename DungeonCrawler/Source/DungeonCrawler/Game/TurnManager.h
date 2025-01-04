// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TurnManager.generated.h"

class ADCPlayerController;
class ABaseCharacterZD;

UENUM(BlueprintType)
enum class EGameTurnState : uint8
{
	TurnStart UMETA(DisplayName = "Turn Start"),
	PlayerTurn UMETA(DisplayName = "Player Turn"),
	EnemyTurn UMETA(DisplayName = "Enemy Turn"),
	TurnEnd UMETA(DisplayName = "Turn End"),
};

UCLASS()
class DUNGEONCRAWLER_API UTurnManager : public UObject
{
	GENERATED_BODY()

public:
	UTurnManager();

	void InitializeTurnManagerData(ABaseCharacterZD* PlayerCharacter, ADCPlayerController* PlayerController);
	void InitializeTurnOrder(const TArray<AActor*>& Participants);
	void StartNextTurn();
	void EndTurn();

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetTurnOrder();
	
	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentActor() const;

	UFUNCTION(BlueprintCallable)
	EGameTurnState GetCurrentTurnState() const;

protected:
	
	int32 CurrentTurnIndex;
	
	UPROPERTY()
	TArray<AActor*> TurnOrder;

	UPROPERTY()
	EGameTurnState CurrentTurnState;

	void ProcessTurn(AActor* CurrentActor);
	void EnablePlayerInput();
	void DisablePlayerInput();
	void ProcessEnemyTurn();

	// Event to register a performed Action
	UFUNCTION()
	void OnActorActionComplete();

	// Event to register a finished Turn
	UFUNCTION()
	void OnActorTurnComplete();
private:
	
	UPROPERTY()
	ADCPlayerController* DCPlayerController;
	
	UPROPERTY()
	ABaseCharacterZD* PlayerCharacterZD;
	
};
// create turn manager in game state
// Gather Participants
// InitializeTurnManager
// InitializeTurnOrder
// StartNextTurn
// Check: 1. Turn progression, 2. Doesn't crash and burn