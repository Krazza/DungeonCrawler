// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurnBasedComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUNGEONCRAWLER_API UTurnBasedComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTurnBasedComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Turn System")
	int32 Initiative;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turn System")
	int32 MaxActions;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Turn System")
	int32 RemainingActions;

	void ResetActions() { RemainingActions = MaxActions; }
	bool CanAct() const { return RemainingActions > 0; }
};
