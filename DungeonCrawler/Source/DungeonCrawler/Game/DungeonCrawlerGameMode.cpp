// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonCrawlerGameMode.h"
#include "DungeonCrawlerGameState.h"
#include "DCPlayerController.h"
#include "GridManager.h"
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
	DungeonGameState->OnGridManagerInitialized.AddDynamic(this, &ADungeonCrawlerGameMode::OnGridManagerInitialized);
}

void ADungeonCrawlerGameMode::InitGameState()
{
	Super::InitGameState();

	ADungeonLevelScriptActor* DungeonLevelScriptActor = Cast<ADungeonLevelScriptActor>(GetWorld()->GetLevelScriptActor());

	if (DungeonLevelScriptActor && DungeonLevelScriptActor->LevelSettings)
	{
		DungeonGameState = GetGameState<ADungeonCrawlerGameState>();
		if (DungeonGameState)
		{
			DungeonGameState->InitializeGridSettings(DungeonLevelScriptActor->LevelSettings);
		}
	}
}

void ADungeonCrawlerGameMode::PositionPlayerCharacter()
{
	if(!GetWorld())
		return;
	
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
