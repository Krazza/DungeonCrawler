// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "DungeonCrawler/Utility/TurnBasedActor.h"
#include "DungeonCrawler/Components/TurnBasedComponent.h"
#include "BaseCharacterZD.generated.h"

class AGridManager;

UCLASS()
class DUNGEONCRAWLER_API ABaseCharacterZD : public APaperZDCharacter, public ITurnBasedActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacterZD();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(FIntPoint Direction, int Steps = 1);

	// For StartingPosition() and alike
	void SetPosition(FIntPoint Position);

	// ***************
	// ITurnBasedActor Interface
	// ***************
	
	virtual int32 GetInitiative() const override { return TurnBasedComponent->Initiative; }
	virtual int32 GetMaxActions() const override { return TurnBasedComponent->MaxActions; }
	virtual int32 GetRemainingActions() const override { return TurnBasedComponent->RemainingActions; }
	virtual void SetRemainingActions(int32 Actions) override { TurnBasedComponent->RemainingActions = Actions; }
	virtual void StartTurn() override { TurnBasedComponent-> ResetActions(); }
	virtual void UseAction() override;
	virtual bool CanAct() const override { return TurnBasedComponent->CanAct(); }

	// Communicating the completion of an Action to the Turn Manager, ITurnBasedActor interface origin
	virtual FTurnActionCompleteDelegate& OnActionComplete() override { return TurnActionCompleteDelegate; }
	
	// Communicating the completion of a Turn to the Turn Manager, ITurnBasedActor interface origin
	virtual FTurnCompleteDelegate& OnTurnComplete() override { return TurnCompleteDelegate; }
private:
	FIntPoint CurrentPosition;

	UPROPERTY()
	AGridManager* GridManager;

	UPROPERTY(BlueprintAssignable, Category = "Turn System")
	FTurnActionCompleteDelegate TurnActionCompleteDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Turn System")
	FTurnCompleteDelegate TurnCompleteDelegate;

	// ***************
	// UTurnBasedComponent
	// ***************

	// Stores Owner's Turn System related data
	UPROPERTY(EditDefaultsOnly, Instanced, Category="Turn System")
	UTurnBasedComponent* TurnBasedComponent;
};
