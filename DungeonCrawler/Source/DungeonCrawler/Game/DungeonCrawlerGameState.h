// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DungeonCrawlerGameState.generated.h"

class AGridManager;
class UPaperTileMap;
class UULevelSettings;
class UTurnManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridManagerInitialized);

UCLASS()
class DUNGEONCRAWLER_API ADungeonCrawlerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADungeonCrawlerGameState();
	
	virtual void BeginPlay() override;
	void CreateTurnManager();

	virtual void InitializeGridSettings(UULevelSettings* LevelSettingsDataAsset);

	UPROPERTY(BlueprintAssignable, Category="Grid")
	FOnGridManagerInitialized OnGridManagerInitialized;
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	AGridManager* GetGridManager() const;
	//Grid parameters 
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	UPaperTileMap* TileMap;
	
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	int32 Rows;
	
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

	UFUNCTION(BlueprintCallable, Category = "Turn System")
	UTurnManager* GetTurnManager() const { return TurnManager; }
protected:
	// Used to spawn the procedural mesh for Grid in editor visualization
	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void HandleGridManagerInitialized();

	UPROPERTY()
	UTurnManager* TurnManager;
private:
	UPROPERTY()
	AGridManager* GridManager;

	void InitializeGridManager();
};
