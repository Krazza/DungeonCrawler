// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawlerGameMode.h"
#include "DungeonCrawlerGameState.h"
#include "DCPlayerController.h"
#include "EngineUtils.h"
#include "GridManager.h"
#include "TurnManager.h"
#include "DungeonCrawler/Characters/BaseCharacterZD.h"
#include "DungeonCrawler/Utility/DungeonLevelScriptActor.h"

ADungeonCrawlerGameMode::ADungeonCrawlerGameMode()
{
	PlayerCharacterZD = nullptr;
	DungeonGameState = nullptr;
	PlayerController = nullptr;
}

void ADungeonCrawlerGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ADCPlayerController>(GetWorld()->GetFirstPlayerController());

	StartGame();
	DungeonGameState->GetGridManager()->FindPath(FIntPoint(1, 1), FIntPoint(3, 6));
}

void ADungeonCrawlerGameMode::InitGameState()
{
	Super::InitGameState();

	ADungeonLevelScriptActor* DungeonLevelScriptActor = Cast<ADungeonLevelScriptActor>(GetWorld()->GetLevelScriptActor());

	DungeonGameState = GetGameState<ADungeonCrawlerGameState>();
	if(DungeonGameState)
	{
		if (DungeonLevelScriptActor && DungeonLevelScriptActor->LevelSettings)
		{
			DungeonGameState->InitializeGridSettings(DungeonLevelScriptActor->LevelSettings);
		}
		DungeonGameState->CreateTurnManager();
	}
}

void ADungeonCrawlerGameMode::StartGame()
{
	// Prepare Grid related stuff
	if(DungeonGameState)
	{
		DungeonGameState->OnGridManagerInitialized.AddDynamic(this, &ADungeonCrawlerGameMode::OnGridManagerInitialized);
	}
	
	// Initiate TurnManager
	if(DungeonGameState && DungeonGameState->GetTurnManager())
	{
		TArray<AActor*> Participants;

		for(TActorIterator<AActor> It(GetWorld()); It; ++It)
		{
			AActor* Actor = *It;
			if(Actor->Tags.Contains("TurnBased"))
			{
				Participants.Add(Actor);
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Participant number: %u"), Participants.Num());
		
		// REFACTOR
		if(!PlayerCharacterZD)
		{
			if(PlayerController)
			{
				PlayerCharacterZD = Cast<ABaseCharacterZD>(PlayerController->GetPawn());
			}
		}
		
		DungeonGameState->GetTurnManager()->InitializeTurnManagerData(PlayerCharacterZD, PlayerController);
		DungeonGameState->GetTurnManager()->InitializeTurnOrder(Participants);
		DungeonGameState->GetTurnManager()->StartNextTurn();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Turn Manager Initialized"));
	}
}

void ADungeonCrawlerGameMode::PositionPlayerCharacter()
{
	if(!GetWorld())
		return;

	// REFACTOR
	if(!PlayerCharacterZD)
	{
		if(PlayerController)
		{
			PlayerCharacterZD = Cast<ABaseCharacterZD>(PlayerController->GetPawn());
		}
	}
	
	if(PlayerCharacterZD)
	{
		PlayerCharacterZD->SetPosition(DungeonGameState->PlayerStartTile);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode failed to set player start position, invalid character reference."));
	}
}

void ADungeonCrawlerGameMode::OnGridManagerInitialized_Implementation()
{
	PositionPlayerCharacter();
}
