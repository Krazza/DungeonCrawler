// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnBasedComponent.h"


// Sets default values for this component's properties
UTurnBasedComponent::UTurnBasedComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Initiative = 1;
	MaxActions = 1;
	RemainingActions = 0;
}


// Called when the game starts
void UTurnBasedComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTurnBasedComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

