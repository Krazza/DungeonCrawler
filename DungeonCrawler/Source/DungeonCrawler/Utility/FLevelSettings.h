#pragma once
#include "CoreMinimal.h"
#include "PaperTileMap.h"
#include "Math/Vector.h"
#include "Containers/Array.h"
#include "FLevelSettings.generated.h"

// DEPRECATED
USTRUCT(BlueprintType)
struct FLevelSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperTileMap* TileMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Grid")
	int32 Rows;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Grid")
	int32 Columns;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Grid")
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Grid")
	FVector GridOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	TArray<int32> ImmovableObstacleIDs;
	
	// DEPRECATED
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	FIntPoint PlayerStartTile;
	// DEPRECATED
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	FIntPoint LevelExitTile;

	FLevelSettings()
	: TileMap(nullptr),
	Rows(20),
	Columns(20),
	TileSize(160.f),
	GridOffset(-TileSize/2, -TileSize/2, 0.f),
	PlayerStartTile(1, 1),
	LevelExitTile(18, 18)
	{}
};

// create data containers according to the lists (paper)