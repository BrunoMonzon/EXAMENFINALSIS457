// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Estado.h"
#include "MaquinaTragamonedasEscuelaVieja.generated.h"

UCLASS()
class TETRIS_UE4_API AMaquinaTragamonedasEscuelaVieja : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaquinaTragamonedasEscuelaVieja();

private:
	//The No Dollars State of this Slot Machine
	IEstado* NoDollarsState;
	//The No Coin State of this Slot Machine
	IEstado* NoCoinState;
	//The Coin Inserted State of this Slot Machine
	IEstado* CoinInsertedState;
	//The Won Dollars State of this Slot Machine
	IEstado* WonDollarsState;
	//The State of this Slot Machine
	IEstado* State;
	//The amount of Dollars of this Slot Machine
	int Count = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Initialize this Slot Machine
	void Initialize(int NumberOfDollars);
	//Insert a Coin
	void InsertCoin();
	//Reject a Coin
	void RejectCoin();
	//Pull the lever of this Slot Machine
	void PullLever();
	//Get the current State of this Slot Machine
	IEstado* GetState();
	//Get the No Dollars State of this Slot Machine
	IEstado* GetNoDollarsState();
	//Get the No Coin State of this Slot Machine
	IEstado* GetNoCoinState();
	//Get the Coin Inserted State of this Slot Machine
	IEstado* GetCoinInsertedState();
	//Get the Won Dollars State of this Slot Machine
	IEstado* GetWonDollarsState();
	//Get the String of the current State
	FString GetCurrentState();
	//Set the Current State with the passed one
	void SetState(IEstado* myState);
	//Emit Dollars from this Slot Machine
	void EmitDollars();
	//Get the amount of dollars in this Slot Machine
	int GetCount();
	//Refill the dollars by the passed amount
	void RestockDollars(int myCount);

};
