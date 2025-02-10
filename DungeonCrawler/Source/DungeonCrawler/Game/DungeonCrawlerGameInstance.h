// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonCrawler/Utility/FLevelConnection.h"
#include "Engine/GameInstance.h"
#include "Templates/SharedPointer.h"
#include "DungeonCrawler/Utility/FLevelDataStruct.h"
#include "DungeonCrawlerGameInstance.generated.h"

class UPaperTileMap;

enum class ETileLayer : uint8
{
	Walls,
	Entrances,
	Exits,
	Rooms,
	Corridors,
	Invalid
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelIndexChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelSequenceGenerated);

UCLASS()
class DUNGEONCRAWLER_API UDungeonCrawlerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UDungeonCrawlerGameInstance();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level Data")
	TArray<FName> LevelOrder;

	// setting start position & exploring map 
	UFUNCTION(BlueprintCallable)
	void SetLevelData(FName LevelName, FLevelDataStruct LevelData);

	UFUNCTION(BlueprintCallable)
	FName GetCurrentDungeonLevelName();

	UFUNCTION(BlueprintCallable)
	FLevelDataStruct& GetCurrentLevelData();

	UFUNCTION(BlueprintCallable)
	FLevelDataStruct& GetPreviousLevelData();

	UFUNCTION(BlueprintCallable)
	FLevelDataStruct& GetNextLevelData();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentLevelIndex();

	UFUNCTION(BlueprintCallable)
	void SetCurrentLevelIndex(int32 LevelIndex);

	UPROPERTY(BlueprintAssignable)
	FOnLevelIndexChanged OnLevelIndexChanged;

	UPROPERTY(BlueprintAssignable)
	FOnLevelSequenceGenerated OnLevelSequenceGenerated;
	// UFUNCTION(BlueprintCallable)
	// void SetConnection(const FName& CurrentLevel, const FIntPoint& CurrentTile, const FName& NextLevel, const FIntPoint& NextTile);
	//
	// UFUNCTION(BlueprintCallable)
	// FLevelConnection GetConnection(const FName& CurrentLevel, const FIntPoint& CurrentTile);
	//
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level Data")
	// TMap<FName, FLevelConnection> AllLevelConnections
	UFUNCTION(BlueprintCallable)
	void CreateLevelSequence();
	
protected:
	
	UFUNCTION(BlueprintCallable)
	FLevelDataStruct CreateLevelDataStruct(FName LevelName, UPaperTileMap* TileMap);

	UFUNCTION(BlueprintCallable)
	TArray<FIntPoint> FillLayerArray(UPaperTileLayer* TileLayer);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Level Data")
	TMap<FName, UPaperTileMap*> LevelGenerationData;
	
private:
	ETileLayer GetTileLayerEnum(const FString& LayerName);
	
	UPROPERTY()
	TMap<FName, FLevelDataStruct> LevelSequence;

	UPROPERTY()
	int32 CurrentLevelIndex;
};

inline int32 UDungeonCrawlerGameInstance::GetCurrentLevelIndex()
{
	return CurrentLevelIndex;
}

