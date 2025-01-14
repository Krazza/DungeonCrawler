#pragma once
#include "CoreMinimal.h"
#include "FLevelConnection.generated.h"

USTRUCT(BlueprintType)
struct FLevelConnection
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ConnectedLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint SharedTile;
};
