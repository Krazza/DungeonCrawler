#pragma once
#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "FLevelDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FLevelDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	FName LevelName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	FIntPoint StartingPosition;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	TArray<FIntPoint> Walls;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	TArray<FIntPoint> Entrances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level Data")
	TArray<FIntPoint> Exits;
	
	FLevelDataStruct()
		:
	LevelName("Debug"),
	Rows(10),
	Columns(10),
	StartingPosition(FIntPoint::ZeroValue)
	{}
	//entrances
	//exits
	//enemies
	//crystals
	//nodes
};
