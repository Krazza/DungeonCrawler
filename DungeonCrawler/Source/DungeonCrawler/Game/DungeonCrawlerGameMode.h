﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonCrawlerGameMode.generated.h"

class ABaseCharacterZD;
class ADCPlayerController;
class ADungeonCrawlerGameState;
class UDungeonCrawlerGameInstance;

UCLASS()
class DUNGEONCRAWLER_API ADungeonCrawlerGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADungeonCrawlerGameMode();
	virtual void BeginPlay() override;
	virtual void PositionPlayerCharacter();
protected:
	virtual void InitGameState() override;

	virtual void StartGame();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Grid")
	void OnGridManagerInitialized();
	virtual void OnGridManagerInitialized_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Grid")
	void OnEndOfLevelReached();
	virtual void OnEndOfLevelReached_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Grid")
	void OnLevelIndexChanged();
	virtual void OnLevelIndexChanged_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Grid")
	void OnLevelSequenceGenerated();
	virtual void OnLevelSequenceGenerated_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Grid")
	void OnPlayerEnteredRoom();
	virtual void OnPlayerEnteredRoom_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Grid")
	void OnPlayerExitedRoom();
	virtual void OnPlayerExitedRoom_Implementation();
private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDungeonCrawlerGameInstance* GameInstance;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ABaseCharacterZD* PlayerCharacterZD;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ADungeonCrawlerGameState* DungeonGameState;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ADCPlayerController* PlayerController;
};
