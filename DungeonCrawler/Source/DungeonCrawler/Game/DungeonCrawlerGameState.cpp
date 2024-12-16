// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCrawlerGameState.h"
#include "PaperTileMap.h"
#include "GridManager.h"
#include "DungeonCrawler/Utility/ULevelSettings.h"
#include "Kismet/GameplayStatics.h"

ADungeonCrawlerGameState::ADungeonCrawlerGameState()
	: TileMap(nullptr),
	Rows(0),
	Columns(0),
	TileSize(0),
	GridOffset(0, 0,0),
	ImmovableObstacleIDs(),
	PlayerStartTile(1,1),
	LevelExitTile(18, 18),
	GridManager(nullptr)
{
	
}

void ADungeonCrawlerGameState::BeginPlay()
{
	Super::BeginPlay();

	//continue here.
	//need to figure out a way to pass a valid GridManager ref. to the GameMode
	//position player character at the start
	if(GridManager)
	{
		GridManager->OnGridManagerInitialized.Broadcast();
		UE_LOG(LogTemp, Display, TEXT("Game State components initialized, Broadcast complete."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No broadcast."));
	}
}

void ADungeonCrawlerGameState::InitializeGridSettings(UULevelSettings* LevelSettingsDataAsset)
{
	if(!LevelSettingsDataAsset)
		return;

	TileMap = LevelSettingsDataAsset->LevelSettings.TileMap;
	Rows = LevelSettingsDataAsset->LevelSettings.Rows;
	Columns = LevelSettingsDataAsset->LevelSettings.Columns;
	TileSize = LevelSettingsDataAsset->LevelSettings.TileSize;
	GridOffset = LevelSettingsDataAsset->LevelSettings.GridOffset;
	ImmovableObstacleIDs = LevelSettingsDataAsset->LevelSettings.ImmovableObstacleIDs;
	PlayerStartTile = LevelSettingsDataAsset->LevelSettings.PlayerStartTile;
	LevelExitTile = LevelSettingsDataAsset->LevelSettings.LevelExitTile;

	InitializeGridManager();
}

void ADungeonCrawlerGameState::InitializeGridManager()
{
	if(!GetWorld()) return;
	
	FVector SpawnLocation(GridOffset.X, GridOffset.Y, 0.f);
	FRotator SpawnRotation(0.f, 0.f, 0.f);
	
	GridManager = GetWorld()->SpawnActorDeferred<AGridManager>(
		AGridManager::StaticClass(),
		FTransform(SpawnRotation, SpawnLocation),
		this,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if(GridManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grid Manager created"));
		GridManager->InitializeGrid(Rows, Columns, TileSize);

		if(TileMap)
		{
			GridManager->UpdateGridBasedOnTileMap(TileMap, ImmovableObstacleIDs);
		}

		UGameplayStatics::FinishSpawningActor(GridManager, FTransform(SpawnRotation, SpawnLocation));
		GridManager->OnGridManagerInitialized.AddDynamic(this, &ADungeonCrawlerGameState::OnGridManagerInitialized);
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

