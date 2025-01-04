// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCrawlerGameState.h"
#include "PaperTileMap.h"
#include "GridManager.h"
#include "TurnManager.h"
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
	TurnManager(nullptr),
	GridManager(nullptr)

{
	
}

void ADungeonCrawlerGameState::BeginPlay()
{
	Super::BeginPlay();
	OnGridManagerInitialized.Broadcast();
}

void ADungeonCrawlerGameState::CreateTurnManager()
{
	if(TurnManager == nullptr)
		TurnManager = NewObject<UTurnManager>(this);
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
	CreateTurnManager();
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
		OnGridManagerInitialized.AddDynamic(this, &ADungeonCrawlerGameState::HandleGridManagerInitialized);
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

