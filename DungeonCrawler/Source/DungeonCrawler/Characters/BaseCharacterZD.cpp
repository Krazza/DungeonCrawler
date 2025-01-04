// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterZD.h"
#include "Kismet/GameplayStatics.h"
#include "DungeonCrawler/Game/DungeonCrawlerGameState.h"
#include "DungeonCrawler/Game/GridManager.h"


// Sets default values
ABaseCharacterZD::ABaseCharacterZD()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GridManager = nullptr;
	CurrentPosition = FIntPoint(0,0);

	TurnBasedComponent = CreateDefaultSubobject<UTurnBasedComponent>(TEXT("TurnBasedComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacterZD::BeginPlay()
{
	Super::BeginPlay();
	if (!GridManager)
	{
		if(ADungeonCrawlerGameState* DungeonGameState = Cast<ADungeonCrawlerGameState>(UGameplayStatics::GetGameState(this)))
		{
			GridManager = DungeonGameState->GetGridManager();
		}
	}
}

// Called every frame
void ABaseCharacterZD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacterZD::Move(FIntPoint Direction, int Steps)
{
	UE_LOG(LogTemp, Warning, TEXT("BaseCharacterZD::Move direction %d, %d"), Direction.X, Direction.Y);
	// DEBUG/TEST
	if(GridManager)
	{
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
			}
		}
	}
}

void ABaseCharacterZD::SetPosition(FIntPoint Position)
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
	UE_LOG(LogTemp, Warning, TEXT("Setting position: %d, %d"), Position.X, Position.Y);
	UE_LOG(LogTemp, Warning, TEXT("Setting position: %f, %f, %f"), newWorldPosition.X, newWorldPosition.Y, newWorldPosition.Z);
}

void ABaseCharacterZD::UseAction()
{
	--TurnBasedComponent->RemainingActions;
	// call the action done delegate
	
	if(!CanAct())
		TurnCompleteDelegate.Broadcast();
}
