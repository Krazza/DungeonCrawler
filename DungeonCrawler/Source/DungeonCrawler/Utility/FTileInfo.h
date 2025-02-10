#pragma once

#include "CoreMinimal.h"
#include "FTileInfo.generated.h"

USTRUCT(BlueprintType)
struct FTileInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsBlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRoomTile;
	
	FTileInfo()
		:
	bIsBlocked(false),
	bIsExit(false),
	bIsRoomTile(false)
	{}
};
