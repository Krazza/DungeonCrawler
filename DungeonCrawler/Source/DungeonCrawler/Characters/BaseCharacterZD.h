// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

#include "BaseCharacterZD.generated.h"

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
private:
	FIntPoint CurrentPosition;
};
