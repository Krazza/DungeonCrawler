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
	AGridManager();
	
	virtual void BeginPlay() override;

	// **************
	// 
	// **************
	
	UFUNCTION(BlueprintCallable, Category="Grid")
	void InitializeGrid(int32 InRows, int32 InColumns, float InTileSize);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetTileState(FIntPoint TilePosition, bool bIsBlocked);
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool IsTileBlocked(FIntPoint Position) const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void UpdateGridBasedOnTileMap(UPaperTileMap* TileMap, const TArray<int32>& ImmovableObstacleIDs);
	
	// *****************
	// 
	// *****************
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	FIntPoint WorldToGridPosition(const FVector& WorldLocation) const;
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	FVector GridToWorldPosition(const FIntPoint& GridLocation, bool bIsCenter) const;

	// ****************
	// 
	// ****************
	
	

	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool IsTileValid(FIntPoint Position) const;
	
	
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	float GetGridHeight() const;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	float GetGridWidth() const;

	// ******************
	// Entity interaction
	// ******************
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void UpdateEntityPosition(AActor* Entity, FIntPoint OldPosition, FIntPoint NewPosition);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	bool isTileOccupiedByEntity(FIntPoint Position);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	AActor* GetActorAtTilePosition(FIntPoint Position);

	// ********************
	// Data from DataAssets
	// ********************
	
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	int32 Rows;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	int32 Columns;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	float TileSize;

private:
	
	TArray<TArray<FTileInfo>> Grid;
	
	UPROPERTY()
	TMap<FIntPoint, AActor*> OccupiedTiles;

	// *************
	// -== DEBUG ==-
	// *************
	
	// Draw console grid
	void DrawDebugGrid();
	void ConstructDebugGrid(TArray<TArray<char>>& GridVisuals);
	void PrintDebugGrid(TArray<TArray<char>>& GridVisuals) const;
};
