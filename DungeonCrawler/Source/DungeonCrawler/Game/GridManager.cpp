// Fill out your copyright notice in the Description page of Project Settings.
#include "GridManager.h"

#include "IContentBrowserSingleton.h"
#include "IPropertyTable.h"
#include "PaperTileLayer.h"
#include "PaperTileMap.h"
#include "Kismet/GameplayStatics.h"

AGridManager::AGridManager()
{
	Rows = 10;
	Columns = 10;
	TileSize = 160.f;
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

bool AGridManager::IsTileBlocked(int32 Row, int32 Column) const
{
	if(Row >=0 && Row < Rows && Column >=0 && Column < Columns)
	{
		return Grid[Row][Column].bIsBlocked;
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
	DrawDebugGrid();
}

void AGridManager::SetTileState(FIntPoint TilePosition, bool bIsBlocked)
{
	//TilePosition.X corresponds to the row (Y-axis)
	//TilePosition.Y corresponds to the column (X-axis)
	if(TilePosition.X >= 0 && TilePosition.X < Rows && TilePosition.Y >= 0 && TilePosition.Y < Columns)
	{
		Grid[TilePosition.X][TilePosition.Y].bIsBlocked = bIsBlocked;
	}
}

FVector2D AGridManager::WorldToGridPosition(const FVector& WorldLocation) const
{
	int32 Row = FMath::FloorToInt(WorldLocation.X/TileSize);
	int32 Column = FMath::FloorToInt(WorldLocation.Y/TileSize);
	return FVector2D(Row, Column);
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
		}
	}
	// place "actors"
	//GridVisuals[2][6] = 'O';
}

void AGridManager::PrintDebugGrid(TArray<TArray<char>>& GridVisuals)
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
