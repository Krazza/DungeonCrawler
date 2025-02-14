// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawlerGameMode.h"
#include "DungeonCrawlerGameState.h"
#include "DCPlayerController.h"
#include "DungeonCrawlerGameInstance.h"
#include "EngineUtils.h"
#include "GridManager.h"
#include "TurnManager.h"
#include "DungeonCrawler/Characters/BaseCharacterZD.h"
#include "DungeonCrawler/Characters/BasePlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ADungeonCrawlerGameMode::ADungeonCrawlerGameMode()
{
	PlayerCharacterZD = nullptr;
	DungeonGameState = nullptr;
	PlayerController = nullptr;
	GameInstance = nullptr;
}

void ADungeonCrawlerGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ADCPlayerController>(GetWorld()->GetFirstPlayerController());
	
	if (DungeonGameState->GetGridManager())
	{
		StartGame();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not StartGame(), no GridManager"));
	}
	//DungeonGameState->GetGridManager()->FindPath(FIntPoint(1, 1), FIntPoint(3, 6));
}

void ADungeonCrawlerGameMode::InitGameState()
{
	Super::InitGameState();
	
	DungeonGameState = GetGameState<ADungeonCrawlerGameState>();
	
	GameInstance = Cast<UDungeonCrawlerGameInstance>(GetGameInstance());
	if(GameInstance)
	{
		GameInstance->OnLevelIndexChanged.AddDynamic(this, &ADungeonCrawlerGameMode::OnLevelIndexChanged);
		GameInstance->OnLevelSequenceGenerated.AddDynamic(this, &ADungeonCrawlerGameMode::OnLevelSequenceGenerated);
		GameInstance->CreateLevelSequence();
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
				PlayerCharacterZD = Cast<ABasePlayerCharacter>(PlayerController->GetPawn());
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
			PlayerCharacterZD = Cast<ABasePlayerCharacter>(PlayerController->GetPawn());
		}
	}
	
	if(PlayerCharacterZD)
	{
		int32 randomIndex = FMath::RandRange(0, GameInstance->GetCurrentLevelData().Entrances.Num() - 1);
		FIntPoint RandomPosition = GameInstance->GetCurrentLevelData().Entrances[randomIndex];
		PlayerCharacterZD->SetPosition(RandomPosition);

		//Might want to separate into 2 or (n) different events in the future
		// one for camera
		// another for whatever
		if(DungeonGameState->GetGridManager()->IsRoomTile(RandomPosition))
		{
			OnPlayerEnteredRoom();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode failed to set player start position, invalid character reference."));
	}
}

void ADungeonCrawlerGameMode::OnGridManagerInitialized_Implementation()
{
	PositionPlayerCharacter();
	DungeonGameState->GetGridManager()->OnEndOfLevelReached.AddDynamic(this, &ADungeonCrawlerGameMode::OnEndOfLevelReached);
	DungeonGameState->GetGridManager()->OnPlayerEnteredRoom.AddDynamic(this, &ADungeonCrawlerGameMode::OnPlayerEnteredRoom);
	DungeonGameState->GetGridManager()->OnPlayerExitedRoom.AddDynamic(this, &ADungeonCrawlerGameMode::OnPlayerExitedRoom);
}

void ADungeonCrawlerGameMode::OnEndOfLevelReached_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("EndOfLevel reached, changing current level index."));
	//update level index in Game Instance
	GameInstance->SetCurrentLevelIndex(GameInstance->GetCurrentLevelIndex() + 1);
}

void ADungeonCrawlerGameMode::OnLevelIndexChanged_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Level index changed, ADungeonCrawlerGameMode::OnLevelIndexChanged"));
	UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetNextLevelData().LevelName);
}

void ADungeonCrawlerGameMode::OnLevelSequenceGenerated_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Mode reacting to level sequence generation"));
	if(DungeonGameState && GameInstance)
	{
		DungeonGameState->InitializeGridManager(GameInstance->GetCurrentLevelData());
		DungeonGameState->CreateTurnManager();
		UE_LOG(LogTemp, Warning, TEXT("Level Sequence Generated"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("DungeonCrawlerGameMode::OnLevelSequenceGenerated()"));
	}
}

void ADungeonCrawlerGameMode::OnPlayerEnteredRoom_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Player entered room"));

	//position camera
}

void ADungeonCrawlerGameMode::OnPlayerExitedRoom_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Player exited room"));

	//reposition camera
}
