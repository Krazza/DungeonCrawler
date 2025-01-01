// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BaseCharacterZD.generated.h"

class AGridManager;

UCLASS()
class DUNGEONCRAWLER_API ABaseCharacterZD : public APaperZDCharacter
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
	// Turn Management
	// ***************
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Turn System")
	int32 Initiative;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn System")
	int32 MaxActions;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Turn System")
	int32 RemainingActions;

	void StartTurn();
	void UseAction();
	bool CanAct() const;

private:
	FIntPoint CurrentPosition;

	UPROPERTY()
	AGridManager* GridManager;
};
