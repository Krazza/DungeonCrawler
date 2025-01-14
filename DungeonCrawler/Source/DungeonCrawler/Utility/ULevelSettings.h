// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FLevelSettings.h"
#include "ULevelSettings.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UULevelSettings : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Settings")
	FLevelSettings LevelSettings;
};
// DEPRECATED