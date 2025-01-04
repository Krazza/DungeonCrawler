#include "TurnManager.h"
#include "DCPlayerController.h"
#include "DungeonCrawler/Utility/TurnBasedActor.h"
#include "DungeonCrawler/Characters/BaseCharacterZD.h"

UTurnManager::UTurnManager()
{
	CurrentTurnIndex = 0;
	CurrentTurnState = EGameTurnState::TurnStart;
	DCPlayerController = nullptr;
	PlayerCharacterZD = nullptr;
}

void UTurnManager::InitializeTurnManagerData(ABaseCharacterZD* PlayerCharacter, ADCPlayerController* PlayerController)
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

	TurnOrder.Sort([](const AActor& A, const AActor& B)
	{
		const ITurnBasedActor* TurnBasedActorA = Cast<ITurnBasedActor>(&A);
		const ITurnBasedActor* TurnBasedActorB = Cast<ITurnBasedActor>(&B);

		if(TurnBasedActorA && TurnBasedActorB)
		{
			return TurnBasedActorA->GetInitiative() > TurnBasedActorB->GetInitiative();
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
	
	UE_LOG(LogTemp, Display, TEXT("Turn Started."));
	
	ProcessTurn(CurrentActor);
}

void UTurnManager::EndTurn()
{
	CurrentTurnState = EGameTurnState::TurnEnd;
	StartNextTurn();
	UE_LOG(LogTemp, Display, TEXT("Turn Ended."));
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
	ITurnBasedActor* TurnBasedActor = Cast<ITurnBasedActor>(CurrentActor);

	if(TurnBasedActor)
	{
		//if player, enable input
		//if not, disable input
		TurnBasedActor->StartTurn();
		//TurnBasedActor->OnActionComplete().AddDynamic(this, &UTurnManager::OnActorActionComplete);
		TurnBasedActor->OnTurnComplete().AddDynamic(this, &UTurnManager::OnActorTurnComplete);
		
		UE_LOG(LogTemp, Display, TEXT("Turn Processed."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor does not implement ITurnBasedActor interface."));
		EndTurn();
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

void UTurnManager::OnActorActionComplete()
{
	ITurnBasedActor* CurrentTurnActor = Cast<ITurnBasedActor>(GetCurrentActor());

	if(CurrentTurnActor)
	{
		// Action specific behavior
		//CurrentTurnActor->OnActionComplete().RemoveDynamic(this, &UTurnManager::OnActorActionComplete);
	}
}

void UTurnManager::OnActorTurnComplete()
{
	ITurnBasedActor* CurrentTurnActor = Cast<ITurnBasedActor>(GetCurrentActor());

	if(CurrentTurnActor)
	{
		// if player, disable input
		CurrentTurnActor->OnTurnComplete().RemoveDynamic(this, &UTurnManager::OnActorTurnComplete);
	}

	EndTurn();
}
