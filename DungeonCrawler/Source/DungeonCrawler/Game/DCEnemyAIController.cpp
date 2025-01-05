// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCrawler/Game/DCEnemyAIController.h"

ADCEnemyAIController::ADCEnemyAIController()
{
	TargetActor = nullptr;
	CurrentDestination = FIntPoint(0, 0);
}

void ADCEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADCEnemyAIController::SetTarget(AActor* NewTarget)
{
	TargetActor = NewTarget;
}

void ADCEnemyAIController::MoveToTile(const FIntPoint& TilePosition)
{
	CurrentDestination = TilePosition;
}
