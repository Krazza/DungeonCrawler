// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DungeonCrawler/Utility/FTileInfo.h"
#include "GridManager.generated.h"

UCLASS(Blueprintable)
class DUNGEONCRAWLER_API UGridManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Grid")
	void InitializeGrid(int32 InRows, int32 InColumns, float InTileSize);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool IsTileBlocked(int32 Row, int32 Column) const;
	
	UFUNCTION(BlueprintCallable, Category="Grid")
	void BlockTilesFromObstacles();

private:
	int32 Rows;
	int32 Columns;
	float TileSize;
	
	TArray<TArray<FTileInfo>> Grid;
};
