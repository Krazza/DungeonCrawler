// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonCrawler/Utility/FTileInfo.h"
#include "GridManager.generated.h"

class UPaperTileMap;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridManagerInitialized);

UCLASS()
class DUNGEONCRAWLER_API AGridManager : public AActor
{
	GENERATED_BODY()

public:
	AGridManager();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category="Grid")
	void InitializeGrid(int32 InRows, int32 InColumns, float InTileSize);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool IsTileBlocked(int32 Row, int32 Column) const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void UpdateGridBasedOnTileMap(UPaperTileMap* TileMap, const TArray<int32>& ImmovableObstacleIDs);
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetTileState(FIntPoint TilePosition, bool bIsBlocked);

	UPROPERTY(BlueprintAssignable, Category="Grid")
	FOnGridManagerInitialized OnGridManagerInitialized;

	//Level DA origin
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	int32 Rows;
	//Level DA origin
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	int32 Columns;
	//Level DA origin
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	float TileSize;
private:
	
	TArray<TArray<FTileInfo>> Grid;

	FVector2D WorldToGridPosition(const FVector& WorldLocation) const;

	// -== DEBUG ==-

	// Console Grid
	void DrawDebugGrid();
	void ConstructDebugGrid(TArray<TArray<char>>& GridVisuals);
	void PrintDebugGrid(TArray<TArray<char>>& GridVisuals);
};
