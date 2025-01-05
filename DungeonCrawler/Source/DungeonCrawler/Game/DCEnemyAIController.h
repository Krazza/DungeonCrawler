// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "DCEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API ADCEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADCEnemyAIController();
	
	virtual void Tick(float DeltaTime) override;

	void SetTarget(AActor* NewTarget);
	void MoveToTile(const FIntPoint& TilePosition);

private:
	UPROPERTY()
	AActor* TargetActor;

	UPROPERTY()
	FIntPoint CurrentDestination;
};
