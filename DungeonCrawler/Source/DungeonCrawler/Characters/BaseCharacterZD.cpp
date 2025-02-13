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
// move to player class
void ABaseCharacterZD::Move(FIntPoint Direction, int Steps)
{
	
}

void ABaseCharacterZD::SetPosition(FIntPoint Position)
{
	
}

void ABaseCharacterZD::UseAction()
{
	--TurnBasedComponent->RemainingActions;
	// call the action done delegate
	
	if(!CanAct())
		TurnCompleteDelegate.Broadcast();
}
