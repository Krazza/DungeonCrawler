// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterZD.h"


// Sets default values
ABaseCharacterZD::ABaseCharacterZD()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacterZD::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacterZD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacterZD::Move(FIntPoint Direction, int Steps)
{
	
}

void ABaseCharacterZD::SetPosition(FIntPoint Position)
{
	CurrentPosition = Position;
}
