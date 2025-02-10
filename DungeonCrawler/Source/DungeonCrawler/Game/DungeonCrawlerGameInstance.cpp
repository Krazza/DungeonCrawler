// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawlerGameInstance.h"
#include "PaperTileLayer.h"
#include "PaperTileMap.h"

UDungeonCrawlerGameInstance::UDungeonCrawlerGameInstance()
{
	CurrentLevelIndex = 0;
	CreateLevelSequence();
}

void UDungeonCrawlerGameInstance::SetLevelData(FName LevelName, FLevelDataStruct LevelData)
{
	if(LevelSequence.Contains(LevelName))
	{
		LevelSequence[LevelName] = LevelData;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to set LevelData, LevelSequence[%s] not found. UDungeonCrawlerGameInstance::SetLevelData"), *LevelName.ToString());
	}
}

FName UDungeonCrawlerGameInstance::GetCurrentDungeonLevelName()
{
	if(CurrentLevelIndex >= 0 || CurrentLevelIndex < LevelOrder.Num())
		return LevelOrder[CurrentLevelIndex];

	return LevelOrder[0];
}

FLevelDataStruct& UDungeonCrawlerGameInstance::GetCurrentLevelData()
{
	return LevelSequence[GetCurrentDungeonLevelName()];
}

FLevelDataStruct& UDungeonCrawlerGameInstance::GetPreviousLevelData()
{
	int32 tempIndex = CurrentLevelIndex - 1;
	if (tempIndex <= 0)
	{
		return LevelSequence[LevelOrder[0]];
	}
	return LevelSequence[LevelOrder[tempIndex]];
}

FLevelDataStruct& UDungeonCrawlerGameInstance::GetNextLevelData()
{
	int32 tempIndex = CurrentLevelIndex + 1;
	if (tempIndex >= LevelOrder.Num())
	{
		return LevelSequence[LevelOrder[LevelOrder.Num() - 1]];
	}
	return LevelSequence[LevelOrder[tempIndex]];
}

void UDungeonCrawlerGameInstance::SetCurrentLevelIndex(int32 LevelIndex)
{
	if(LevelIndex >= 0 && LevelIndex < LevelOrder.Num())
	{
		CurrentLevelIndex = LevelIndex;
		OnLevelIndexChanged.Broadcast();
	}
}

//void UDungeonCrawlerGameInstance::SetConnection(const FName& CurrentLevel, const FIntPoint& CurrentTile, const FName& NextLevel, const FIntPoint& NextTile)
// {}
//FLevelConnection UDungeonCrawlerGameInstance::GetConnection(const FName& CurrentLevel, const FIntPoint& CurrentTile)
// {}

void UDungeonCrawlerGameInstance::CreateLevelSequence()
{
	if(LevelSequence.Num() == 0)
	{
		TArray<FName> Keys;
		LevelGenerationData.GetKeys(Keys);
		UPaperTileMap* TileMap = nullptr;
		for(FName Key : Keys)
		{
			TileMap = LevelGenerationData[Key];
			LevelSequence.Add(Key, CreateLevelDataStruct(Key, TileMap));
		}
		UE_LOG(LogTemp, Warning, TEXT("Level Sequence Generated"));
	}
	
	OnLevelSequenceGenerated.Broadcast();
}

FLevelDataStruct UDungeonCrawlerGameInstance::CreateLevelDataStruct(FName LevelName, UPaperTileMap* TileMap)
{
	FLevelDataStruct LevelDataStruct;
	LevelDataStruct.LevelName = LevelName;
	LevelDataStruct.Rows = TileMap->MapHeight;
	LevelDataStruct.Columns = TileMap->MapWidth;

	if(TileMap)
	{
		for(UPaperTileLayer* TileLayer : TileMap->TileLayers)
		{
			ETileLayer LayerEnum = GetTileLayerEnum(TileLayer->LayerName.ToString());
			switch (LayerEnum) 
			{
			case ETileLayer::Walls:
				LevelDataStruct.Walls = FillLayerArray(TileLayer);
				break;
			case ETileLayer::Entrances:
				LevelDataStruct.Entrances = FillLayerArray(TileLayer);
				break;
			case ETileLayer::Exits:
				LevelDataStruct.Exits = FillLayerArray(TileLayer);
				break;
			case ETileLayer::Rooms:
				{
					TSet<FIntPoint> RoomTiles;
					RoomTiles.Append(FillLayerArray(TileLayer));
					LevelDataStruct.RoomTiles = RoomTiles;
				}
				break;
			case ETileLayer::Corridors:
				{
					TSet<FIntPoint> CorridorTiles;
					CorridorTiles.Append(FillLayerArray(TileLayer));
					LevelDataStruct.CorridorTiles = CorridorTiles;
				}
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("Invalid LayerName (%s), DungeonCrawlerGameInstance.cpp"), *TileLayer->LayerName.ToString());
				break;
			}
		}
	}

	return LevelDataStruct;
}

TArray<FIntPoint> UDungeonCrawlerGameInstance::FillLayerArray(UPaperTileLayer* TileLayer)
{
	TArray<FIntPoint> LayerArray;
	for(int32 LayerRow = 0; LayerRow < TileLayer->GetLayerHeight(); LayerRow++)
	{
		for(int32 LayerColumn = 0; LayerColumn < TileLayer->GetLayerWidth(); LayerColumn++)
		{
			FPaperTileInfo PaperTileInfo = TileLayer->GetCell(LayerColumn, LayerRow);
			if(PaperTileInfo.IsValid())
			{
				LayerArray.Push(FIntPoint(LayerRow, LayerColumn));
			}
		}
	}
	return LayerArray;
}

ETileLayer UDungeonCrawlerGameInstance::GetTileLayerEnum(const FString& LayerName)
{
	FString UpperLayerName = LayerName.ToUpper();
	if (UpperLayerName == "WALLS") return ETileLayer::Walls;
	if (UpperLayerName == "ENTRANCES") return ETileLayer::Entrances;
	if (UpperLayerName == "EXITS") return ETileLayer::Exits;
	if (UpperLayerName == "ROOMS") return ETileLayer::Rooms;
	if (UpperLayerName == "CORRIDORS") return ETileLayer::Corridors;
	return ETileLayer::Invalid;
}
