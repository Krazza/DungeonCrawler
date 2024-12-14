// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ULevelSettings.h"
#include "Engine/LevelScriptActor.h"
#include "DungeonLevelScriptActor.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ADungeonLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADungeonLevelScriptActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level Gameplay Settings")
	UULevelSettings* LevelSettings;
};
