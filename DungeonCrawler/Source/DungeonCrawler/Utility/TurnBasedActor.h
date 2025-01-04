// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TurnBasedActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnActionCompleteDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTurnCompleteDelegate);

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UTurnBasedActor : public UInterface
{
	GENERATED_BODY()
};

class DUNGEONCRAWLER_API ITurnBasedActor
{
	GENERATED_BODY()
	
public:
	// Turn system properties
	virtual int32 GetInitiative() const = 0;
	virtual int32 GetMaxActions() const = 0;
	virtual int32 GetRemainingActions() const = 0;
	virtual void SetRemainingActions(int32 Actions) = 0;

	// Turn system behavior
	virtual void StartTurn() = 0;
	virtual void UseAction() = 0;
	virtual bool CanAct() const = 0;

	// Event for action completion
	virtual FTurnActionCompleteDelegate& OnActionComplete() = 0;
	virtual FTurnCompleteDelegate& OnTurnComplete() = 0;
};
