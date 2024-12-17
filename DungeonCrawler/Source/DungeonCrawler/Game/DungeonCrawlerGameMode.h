﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonCrawlerGameMode.generated.h"

class ABaseCharacterZD;
class ADCPlayerController;
class ADungeonCrawlerGameState;

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
	
	UFUNCTION(BlueprintNativeEvent, Category = "Grid")
	void OnGridManagerInitialized();
	virtual void OnGridManagerInitialized_Implementation();
	
private:
	UPROPERTY()
	ABaseCharacterZD* PlayerCharacterZD;

	UPROPERTY()
	ADungeonCrawlerGameState* DungeonGameState;

	UPROPERTY()
	ADCPlayerController* PlayerController;
};
