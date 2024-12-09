// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonCrawler/Utility/FTileInfo.h"
#include "GridManager.generated.h"

class UPaperTileMap;

UCLASS()
class DUNGEONCRAWLER_API AGridManager : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category="Grid")
	void InitializeGrid(int32 InRows, int32 InColumns, float InTileSize);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool IsTileBlocked(int32 Row, int32 Column) const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void UpdateGridBasedOnTileMap(UPaperTileMap* TileMap, const TArray<int32>& ImmovableObstacleIDs);
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetTileState(FIntPoint TilePosition, bool bIsBlocked);

private:
	int32 Rows;
	int32 Columns;
	float TileSize;
	
	TArray<TArray<FTileInfo>> Grid;

	FVector2D WorldToGridPosition(const FVector& WorldLocation) const;

	// -== DEBUG ==-
	void DrawDebugGrid();
	void ConstructDebugGrid(TArray<TArray<char>>& GridVisuals);
	void PrintDebugGrid(TArray<TArray<char>>& GridVisuals);
};
