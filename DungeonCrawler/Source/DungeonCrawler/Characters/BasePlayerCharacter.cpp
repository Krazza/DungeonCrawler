// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCharacter.h"

#include "DungeonCrawler/Game/DungeonCrawlerGameState.h"
#include "DungeonCrawler/Game/GridManager.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABasePlayerCharacter::ABasePlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePlayerCharacter::Move(FIntPoint Direction, int Steps)
{
	if(GridManager)
	{
		FIntPoint oldPosition = CurrentPosition;
		FIntPoint newPosition = CurrentPosition + Direction;
		if(GridManager->IsTileValid(newPosition) && !GridManager->IsTileBlocked(newPosition))
		{
			if(CanAct())
			{
				UseAction();
				SetActorLocation(GridManager->GridToWorldPosition(FIntPoint(newPosition.X, newPosition.Y), true));
				//update entity tracked array
				GridManager->UpdateEntityPosition(this, CurrentPosition, newPosition);
				CurrentPosition = newPosition;
				
				if(GridManager->IsExitTile(CurrentPosition))
				{
					GridManager->OnEndOfLevelReached.Broadcast();
				}
				
				if(GridManager->IsRoomTile(CurrentPosition) && !GridManager->IsRoomTile(oldPosition))
				{
					//switch to a broadcasting method?
					//notify the game mode
					//position the camera
					
					//TSet<FIntPoint> OutRoomTiles;
					//GridManager->GetRoomTiles(CurrentPosition, OutRoomTiles);

					GridManager->OnPlayerEnteredRoom.Broadcast();
				}
				else if(GridManager->IsRoomTile(oldPosition) && !GridManager->IsRoomTile(CurrentPosition))
				{
					GridManager->OnPlayerExitedRoom.Broadcast();
				}
			}
		}
	}
}

void ABasePlayerCharacter::SetPosition(FIntPoint Position)
{
	if (!GridManager)
	{
		if(ADungeonCrawlerGameState* DungeonGameState = Cast<ADungeonCrawlerGameState>(UGameplayStatics::GetGameState(this)))
		{
			GridManager = DungeonGameState->GetGridManager();
		}
	}

	if(!GridManager)
	{
		UE_LOG(LogTemp, Error, TEXT("GridManager is null"));
		return;
	}
	
	FVector newWorldPosition = GridManager->GridToWorldPosition(Position, true);
	SetActorLocation(newWorldPosition);
	CurrentPosition = Position;

	if(GridManager->IsRoomTile(CurrentPosition))
	{
		//switch to a broadcasting method?
		//notify the game mode
		//position the camera
		//TSet<FIntPoint> OutRoomTiles;
		//GridManager->GetRoomTiles(CurrentPosition, OutRoomTiles);
		
		GridManager->OnPlayerEnteredRoom.Broadcast();
	}
}

