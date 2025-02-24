// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DungeonCrawlerGameState.generated.h"

struct FLevelDataStruct;
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

	UFUNCTION(BlueprintCallable)
	void InitializeGridManager(FLevelDataStruct& LevelData);
	
	UPROPERTY(BlueprintAssignable, Category="Grid")
	FOnGridManagerInitialized OnGridManagerInitialized;
	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	AGridManager* GetGridManager() const;

	UFUNCTION(BlueprintCallable, Category = "Turn System")
	UTurnManager* GetTurnManager() const { return TurnManager; }
protected:
	// Used to spawn the procedural mesh for Grid in editor visualization
	UFUNCTION(BlueprintNativeEvent, Category = "Grid")
	void HandleGridManagerInitialized();
	virtual void HandleGridManagerInitialized_Implementation();

	UPROPERTY()
	UTurnManager* TurnManager;
private:
	UPROPERTY()
	AGridManager* GridManager;
};
