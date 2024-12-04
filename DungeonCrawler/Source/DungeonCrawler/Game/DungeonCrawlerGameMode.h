// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "DungeonCrawlerGameMode.generated.h"

class UGridManager;

UCLASS()
class DUNGEONCRAWLER_API ADungeonCrawlerGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category="Grid")
	UGridManager* GridManager;
};
