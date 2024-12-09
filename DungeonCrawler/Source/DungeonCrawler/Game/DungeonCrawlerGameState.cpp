// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCrawlerGameState.h"
#include "PaperTileMap.h"
#include "GridManager.h"

ADungeonCrawlerGameState::ADungeonCrawlerGameState()
	: GridManager(nullptr)
{
	TileMap = nullptr;
	//GET from a level DataAsset
	ImmovableObstacleIDs = {0, 1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 35, 40, 41, 42, 43, 44, 45, 50, 51, 52, 53, 54, 55, 78};
}

void ADungeonCrawlerGameState::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeGridManager();
}

void ADungeonCrawlerGameState::InitializeGridManager()
{
	if(!GetWorld()) return;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GridManager = GetWorld()->SpawnActor<AGridManager>(AGridManager::StaticClass(), FVector::Zero(), FRotator());

	if(GridManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid Manager created"));
		//Grid parameters (number of rows and columns) have to be identical to TileMap parameters
		//GET from a level DataAsset
		GridManager->InitializeGrid(20, 20, 160.f);

		if(TileMap)
		{
			GridManager->UpdateGridBasedOnTileMap(TileMap, ImmovableObstacleIDs);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create Grid Manager"));
	}
}

AGridManager* ADungeonCrawlerGameState::GetGridManager() const
{
	return GridManager;
}

