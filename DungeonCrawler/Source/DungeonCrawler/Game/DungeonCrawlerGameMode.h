// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DungeonCrawlerGameMode.generated.h"

class ABaseCharacterZD;

UCLASS()
class DUNGEONCRAWLER_API ADungeonCrawlerGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADungeonCrawlerGameMode();
	virtual void BeginPlay() override;
protected:
	virtual void InitGameState() override;
	virtual void PositionPlayerCharacter();

	UFUNCTION(BlueprintNativeEvent, Category = "Grid")
	void OnGridManagerInitialized();
	virtual void OnGridManagerInitialized_Implementation();
	
private:
	UPROPERTY()
	ABaseCharacterZD* PlayerCharacterZD;
};
