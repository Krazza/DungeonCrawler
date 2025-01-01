#include "TurnManager.h"
#include "DCPlayerController.h"
#include "DungeonCrawler/Characters/BaseCharacterZD.h"

UTurnManager::UTurnManager()
{
	CurrentTurnIndex = 0;
	CurrentTurnState = EGameTurnState::TurnStart;
	DCPlayerController = nullptr;
	PlayerCharacterZD = nullptr;
}

void UTurnManager::InitializeTurnManager(ABaseCharacterZD* PlayerCharacter, ADCPlayerController* PlayerController)
{
	if(PlayerCharacter)
	{
		PlayerCharacterZD = PlayerCharacter;
	}

	if(PlayerController)
	{
		DCPlayerController = PlayerController;
	}
}

void UTurnManager::InitializeTurnOrder(const TArray<AActor*>& Participants)
{
	TurnOrder.Empty();
	TurnOrder = Participants;

	TurnOrder.Sort([](const TArray<AActor*>& A, const TArray<AActor*>& B)
	{
		const ABaseCharacterZD* CharacterA = Cast<ABaseCharacterZD>(&A);
		const ABaseCharacterZD* CharacterB = Cast<ABaseCharacterZD>(&B);

		if(CharacterA && CharacterB)
		{
			return CharacterA->Initiative > CharacterB->Initiative;
		}
		
		return false;
	});

	CurrentTurnIndex = 0;
	CurrentTurnState = EGameTurnState::TurnStart;
}

void UTurnManager::StartNextTurn()
{
	if(TurnOrder.Num() == 0)
		return;

	CurrentTurnIndex = (CurrentTurnIndex + 1) % TurnOrder.Num();
	AActor* CurrentActor = TurnOrder[CurrentTurnIndex];
	CurrentTurnState = (Cast<ADCPlayerController>(CurrentActor->GetOwner()) != nullptr)
	? EGameTurnState::TurnEnd : EGameTurnState::TurnStart;
	
	ProcessTurn(CurrentActor);
}

void UTurnManager::EndTurn()
{
	CurrentTurnState = EGameTurnState::TurnEnd;
	StartNextTurn();
}

TArray<AActor*> UTurnManager::GetTurnOrder()
{
	return TurnOrder;
}

AActor* UTurnManager::GetCurrentActor() const
{
	if(TurnOrder.Num() == 0)
		return nullptr;

	return TurnOrder[CurrentTurnIndex];
		
}

EGameTurnState UTurnManager::GetCurrentTurnState() const
{
	return CurrentTurnState;
}

void UTurnManager::ProcessTurn(AActor* CurrentActor)
{
	ABaseCharacterZD* Character = Cast<ABaseCharacterZD>(CurrentActor);

	if(Character)
	{
		if(Character->IsPlayerControlled())
		{
			EnablePlayerInput();
		}
		else
		{
			DisablePlayerInput();
			ProcessEnemyTurn();
		}

		while(Character->CanAct())
		{
			
		}

		UE_LOG(LogTemp, Warning, TEXT("Action made"));
		
		if(!Character->CanAct())
		{
			EndTurn();
		}
	}
}

void UTurnManager::EnablePlayerInput()
{
	if(DCPlayerController)
	{
		DCPlayerController->EnableInput(DCPlayerController);
		UE_LOG(LogTemp, Warning, TEXT("Player Input Enabled"));
	}
}

void UTurnManager::DisablePlayerInput()
{
	if(DCPlayerController)
	{
		DCPlayerController->DisableInput(DCPlayerController);
		UE_LOG(LogTemp, Warning, TEXT("Player Input Disabled"));
	}
}

void UTurnManager::ProcessEnemyTurn()
{
	// AIbehaviorTree-> Switch keys -> Do some wild shit();
	UE_LOG(LogTemp, Display, TEXT("Processing Enemy Turn"));
}
