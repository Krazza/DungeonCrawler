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
}

void ADungeonCrawlerGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ADungeonCrawlerGameMode::InitGameState()
{
	Super::InitGameState();

	ADungeonLevelScriptActor* DungeonLevelScriptActor = Cast<ADungeonLevelScriptActor>(GetWorld()->GetLevelScriptActor());

	if (DungeonLevelScriptActor && DungeonLevelScriptActor->LevelSettings)
	{
		ADungeonCrawlerGameState* DungeonGameState = GetGameState<ADungeonCrawlerGameState>();
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
		ADCPlayerController* PlayerController = Cast<ADCPlayerController>(GetWorld()->GetFirstPlayerController());
		if(PlayerController)
		{
			PlayerCharacterZD = Cast<ABaseCharacterZD>(PlayerController->GetPawn());
		}
	}
	if(PlayerCharacterZD)
	{
		//PlayerCharacterZD->SetPosition()
	}
}

void ADungeonCrawlerGameMode::OnGridManagerInitialized_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("GameMode registered the GridManager initialization."));
}
