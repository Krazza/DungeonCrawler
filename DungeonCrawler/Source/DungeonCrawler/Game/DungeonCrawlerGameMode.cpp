// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawlerGameMode.h"
#include "DungeonCrawler/Game/GridManager.h"

void ADungeonCrawlerGameMode::BeginPlay()
{
	Super::BeginPlay();

	GridManager = NewObject<UGridManager>();
	if(GridManager)
	{
		GridManager->InitializeGrid(10, 10, 200.f); 
	}
}
