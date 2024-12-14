// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DungeonCrawlerGameState.generated.h"

class AGridManager;
class UPaperTileMap;
class UULevelSettings;

UCLASS()
class DUNGEONCRAWLER_API ADungeonCrawlerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADungeonCrawlerGameState();
	
	virtual void BeginPlay() override;

	virtual void InitializeGridSettings(UULevelSettings* LevelSettingsDataAsset);
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	AGridManager* GetGridManager() const;
	//Grid parameters 
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	UPaperTileMap* TileMap;
	//(number of rows and columns) have to be identical to TileMap parameters
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	int32 Rows;
	//(number of rows and columns) have to be identical to TileMap parameters
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	int32 Columns;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	float TileSize;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	FVector GridOffset;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<int32> ImmovableObstacleIDs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	FIntPoint PlayerStartTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	FIntPoint LevelExitTile;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnGridManagerInitialized();

	virtual void PostInitializeComponents() override;
private:
	UPROPERTY()
	AGridManager* GridManager;

	void InitializeGridManager();
};
