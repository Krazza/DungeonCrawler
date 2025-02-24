// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonCrawlerGameState.h"

#include "DungeonCrawlerGameInstance.h"
#include "GridManager.h"
#include "TurnManager.h"
#include "DungeonCrawler/Utility/FLevelDataStruct.h"
#include "Kismet/GameplayStatics.h"

ADungeonCrawlerGameState::ADungeonCrawlerGameState()
{
	GridManager = nullptr;
	TurnManager = nullptr;
}

void ADungeonCrawlerGameState::BeginPlay()
{
	Super::BeginPlay();
	//potential problem, fix later :)
	OnGridManagerInitialized.Broadcast();
}

void ADungeonCrawlerGameState::CreateTurnManager()
{
	if(TurnManager == nullptr)
		TurnManager = NewObject<UTurnManager>(this);
}

void ADungeonCrawlerGameState::InitializeGridManager(FLevelDataStruct& LevelData)
{
	if(!GetWorld()) return;
	// - tilesize/2
	FVector SpawnLocation(-LevelData.TileSize/2, -LevelData.TileSize/2, 0.f);
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
		GridManager->InitializeGrid(LevelData.Rows, LevelData.Columns, LevelData.TileSize);
		GridManager->UpdateGridBasedOnLevelData(LevelData);

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

void ADungeonCrawlerGameState::HandleGridManagerInitialized_Implementation()
{
	
}

