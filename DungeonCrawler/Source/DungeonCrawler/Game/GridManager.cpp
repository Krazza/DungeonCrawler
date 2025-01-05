﻿// Fill out your copyright notice in the Description page of Project Settings.
#include "GridManager.h"

#include "IContentBrowserSingleton.h"
#include "IPropertyTable.h"
#include "PaperTileLayer.h"
#include "PaperTileMap.h"
#include "DungeonCrawler/Utility/FAStarNode.h"
#include "Kismet/GameplayStatics.h"

AGridManager::AGridManager()
{
	Rows = 10;
	Columns = 10;
	TileSize = 160.f;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComponent);
}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();
}

void AGridManager::InitializeGrid(int32 InRows, int32 InColumns, float InTileSize)
{
	Rows = InRows;
	Columns = InColumns;
	TileSize = InTileSize;
	
	Grid.SetNum(Rows);
	for(int32 Row = 0; Row < Rows; Row++)
	{
		Grid[Row].SetNum(Columns);
		for(int32 Column = 0; Column < Columns; Column++)
		{
			Grid[Row][Column] = FTileInfo();
		}
	}
}

void AGridManager::SetTileState(FIntPoint TilePosition, bool bIsBlocked)
{
	//Tilemaps in unreal go (Y, X) or some shit
	//TilePosition.X corresponds to the row (Y-axis)
	//TilePosition.Y corresponds to the column (X-axis)
	if(TilePosition.X >= 0 && TilePosition.X < Rows && TilePosition.Y >= 0 && TilePosition.Y < Columns)
	{
		Grid[TilePosition.X][TilePosition.Y].bIsBlocked = bIsBlocked;
	}
}

bool AGridManager::IsTileBlocked(FIntPoint(Position)) const
{
	if(Position.X > 0 && Position.X < Rows && Position.Y > 0 && Position.Y < Columns)
	{
		return Grid[Position.X][Position.Y].bIsBlocked;
	}
	return true;
}

void AGridManager::UpdateGridBasedOnTileMap(UPaperTileMap* TileMap, const TArray<int32>& ImmovableObstacleIDs)
{
	if(!TileMap)
	{
		UE_LOG(LogTemp, Error, TEXT("TileMap is NULL"));
		return;
	}
	
	for (UPaperTileLayer* layer : TileMap->TileLayers)
	{
		if(layer->LayerName.ToString().Equals(TEXT("Walls")))//swap for a string variable?
		{
			for(int32 LayerRow = 0; LayerRow < layer->GetLayerHeight(); LayerRow++)//:: WARNING :: needs to be tested with a non-square grid
			{
				for(int32 LayerColumn = 0; LayerColumn < layer->GetLayerWidth(); LayerColumn++)//:: WARNING :: needs to be tested with a non-square grid
				{
					FPaperTileInfo PaperTileInfo = layer->GetCell(LayerColumn, LayerRow);
					if(PaperTileInfo.IsValid())
					{
						int32 TileIndex = PaperTileInfo.GetTileIndex();
						SetTileState(FIntPoint(LayerRow, LayerColumn), ImmovableObstacleIDs.Contains(TileIndex));
					}
				}
			}
		}
	}
	//DEBUG GRID VISUALIZATION
	//DrawDebugGrid();
}

float AGridManager::GetGridHeight() const
{
	return TileSize * Rows;
}

float AGridManager::GetGridWidth() const
{
	return TileSize * Columns;
}

FIntPoint AGridManager::WorldToGridPosition(const FVector& WorldLocation) const
{
	int32 Row = FMath::FloorToInt(((WorldLocation.X - GetActorLocation().X)/GetGridHeight()) * Rows);
	int32 Column = FMath::FloorToInt(((WorldLocation.Y - GetActorLocation().Y)/GetGridWidth()) * Columns);

	if(IsTileValid(FIntPoint(Row, Column)))
		return FIntPoint(Row, Column);
	
	return FIntPoint(0, 0);
}

FVector AGridManager::GridToWorldPosition(const FIntPoint& GridLocation, bool bIsCenter) const
{
	if(IsTileValid(GridLocation))
	{
		float X = GridLocation.X * TileSize + GetActorLocation().X;
		float Y = GridLocation.Y * TileSize + GetActorLocation().Y;
		float Z = 20.f;

		if(bIsCenter)
		{
			X += TileSize/2;
			Y += TileSize/2;
		}
		
		return FVector(Y, X, Z);
	}
	return FVector(0.f, 0.f, 0.f);
}

bool AGridManager::IsTileValid(FIntPoint Position) const
{
	if(Position.X > 0 && Position.X < Rows && Position.Y > 0 && Position.Y < Columns)
		return true;

	return false;
}

// Entity interaction
void AGridManager::UpdateEntityPosition(AActor* Entity, FIntPoint OldPosition, FIntPoint NewPosition)
{
	if(OccupiedTiles.Contains(OldPosition))
	{
		OccupiedTiles.Remove(OldPosition);
	}
	OccupiedTiles.Add(NewPosition, Entity);
	DrawDebugGrid();
}

bool AGridManager::isTileOccupiedByEntity(FIntPoint Position)
{
	return OccupiedTiles.Contains(Position);
}

AActor* AGridManager::GetActorAtTilePosition(FIntPoint Position)
{
	return OccupiedTiles.FindRef(Position);
}

TArray<FIntPoint> AGridManager::FindPath(const FIntPoint& Start, const FIntPoint& Goal)
{
	if(!IsTileValid(Start) || !IsTileValid(Goal) || IsTileBlocked(Start) || IsTileBlocked(Goal))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Start or Goal Tile"));
		return TArray<FIntPoint>();
	}

	TSet<FIntPoint> OpenSet;
	TSet<FIntPoint> ClosedSet;
	TMap<FIntPoint, FAStarNode*> NodeMap;

	FAStarNode* StartNode = new FAStarNode(Start, 0.f, CalculateManhattanDistance(Start, Goal));
	OpenSet.Add(Start);
	NodeMap.Add(Start, StartNode);

	while(OpenSet.Num() > 0)
	{
		//Finding the node with the lowest cost (F)
		FAStarNode* CurrentNode = nullptr;
		for(FIntPoint NodePosition : OpenSet)
		{
			if(!CurrentNode || NodeMap[NodePosition]->FScore < CurrentNode->FScore)
			{
				CurrentNode = NodeMap[NodePosition];
			}
		}
		//Builds the path if the goal was reached
		if(CurrentNode->Position == Goal)
		{
			TArray<FIntPoint> Path;
			while(CurrentNode)
			{
				Path.Add(CurrentNode->Position);
				CurrentNode = CurrentNode->Parent;
			}
			Algo::Reverse(Path);
			// DEBUG
			DrawDebugPath(Path);
			return Path;
		}
		//updating the lists
		OpenSet.Remove(CurrentNode->Position);
		ClosedSet.Add(CurrentNode->Position);

		//explore neighbors
		TArray<FIntPoint> Neighbors = GetTileNeighbors(CurrentNode->Position);
		for(FIntPoint Neighbor : Neighbors)
		{
			if(ClosedSet.Contains(Neighbor) || IsTileBlocked(Neighbor))
				continue;

			float GScore = CurrentNode->GScore + 1;//uniform cost

			// To get a custom cost we need to:
			// 1. address the Grid<FTileInfo>[]
			// 2. check the tile type/active effects/etc.
			// 3. translate tile state into a cost
			// 4. update GScore here

			
			if(!OpenSet.Contains(Neighbor))
			{
				float HScore = CalculateManhattanDistance(Neighbor, Goal);
				FAStarNode* NeighborNode = new FAStarNode(Neighbor, GScore, HScore, CurrentNode);
				OpenSet.Add(Neighbor);
				NodeMap.Add(Neighbor, NeighborNode);
			}
			else if (GScore < NodeMap[Neighbor]->GScore)
			{
				FAStarNode* NeighborNode = NodeMap[Neighbor];
				NeighborNode->GScore = GScore;
				NeighborNode->FScore = GScore + NeighborNode->HScore;
				NeighborNode->Parent = CurrentNode;
			}
		}
	}

	for(auto& Pair : NodeMap)
	{
		delete Pair.Value;
	}
	return {};
}

TArray<FIntPoint> AGridManager::GetTileNeighbors(const FIntPoint& Position) const
{
	TArray<FIntPoint> Neighbors;

	TArray<FIntPoint> Directions =
		{FIntPoint(-1, 0), FIntPoint(1, 0), FIntPoint(0, 1), FIntPoint(0, -1)};

	for(const FIntPoint& Dir : Directions)
	{
		FIntPoint Neighbor = Position + Dir;
		if(IsTileValid(Neighbor) && !IsTileBlocked(Neighbor))
		{
			Neighbors.Add(Neighbor);
		}
	}
	return Neighbors;
}

//**************
// -== DEBUG ==-
//**************
void AGridManager::DrawDebugGrid()
{
	TArray<TArray<char>> GridVisuals;
	GridVisuals.SetNum(Rows);

	ConstructDebugGrid(GridVisuals);
	PrintDebugGrid(GridVisuals);
}

void AGridManager::ConstructDebugGrid(TArray<TArray<char>>& GridVisuals)
{
	for(int32 Row = 0; Row < Rows; Row++)
	{
		GridVisuals[Row].SetNum(Columns);

		for(int32 Column = 0; Column < Columns; Column++)
		{
			// Block a specific tile for testing
			//if(Row == 3 && Column == 9)
			//{
			//	SetTileState(FIntPoint(Row, Column), true);
			//}
			GridVisuals[Row][Column] = Grid[Row][Column].bIsBlocked ? 'X' : '.';

			if(isTileOccupiedByEntity(FIntPoint(Row, Column)))
			{
				GridVisuals[Row][Column] = 'O';
			}
		}
	}
}

void AGridManager::PrintDebugGrid(TArray<TArray<char>>& GridVisuals) const
{
	for(int32 Row = 0; Row < Rows; Row++)
	{
		FString RowString;
		for(int32 Column = 0; Column < Columns; Column++)
		{
			RowString.AppendChar(GridVisuals[Row][Column]);
		}
		UE_LOG(LogTemp, Warning, TEXT("%s"), *RowString);
	}
}

float AGridManager::CalculateManhattanDistance(const FIntPoint& Start, const FIntPoint& Goal)
{
	return FMath::Abs(Start.X - Goal.X) + FMath::Abs(Start.Y - Goal.Y);
}

void AGridManager::DrawDebugPath(const TArray<FIntPoint>& Path)
{
	for(int32 i = 0; i < Path.Num() - 1; ++i)
	{
		FVector Start = GridToWorldPosition(Path[i], true);
		FVector End = GridToWorldPosition(Path[i + 1], true);
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);
	}
}
