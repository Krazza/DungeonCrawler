// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FLevelDataStruct.h"
#include "Engine/DataAsset.h"
#include "LevelDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API ULevelDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelDataAsset")
	FLevelDataStruct LevelData;
};
