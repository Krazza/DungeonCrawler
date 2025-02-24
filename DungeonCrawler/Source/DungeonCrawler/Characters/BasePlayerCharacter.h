// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacterZD.h"
#include "BasePlayerCharacter.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ABasePlayerCharacter : public ABaseCharacterZD
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Move(FIntPoint Direction, int Steps = 1) override;

	// For StartingPosition() and alike
	virtual void SetPosition(FIntPoint newGridPosition) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TileDiscoveryDistance;
};
