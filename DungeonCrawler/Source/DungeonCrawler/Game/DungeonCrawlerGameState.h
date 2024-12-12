// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DungeonCrawlerGameState.generated.h"

class AGridManager;
class UPaperTileMap;

UCLASS()
class DUNGEONCRAWLER_API ADungeonCrawlerGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADungeonCrawlerGameState();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	AGridManager* GetGridManager() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	UPaperTileMap* TileMap;

	//Walls & obstacles
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<int32> ImmovableObstacleIDs;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnGridManagerInitialized();
private:
	UPROPERTY()
	AGridManager* GridManager;

	void InitializeGridManager();
};
