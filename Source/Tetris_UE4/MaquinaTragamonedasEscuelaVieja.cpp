// Fill out your copyright notice in the Description page of Project Settings.


#include "MaquinaTragamonedasEscuelaVieja.h"
#include "EstadoSinDolares.h"
#include "EstadoSinMonedas.h"
#include "EstadoMonedaInsertada.h"
#include "EstadoGanoDolares.h"

// Sets default values
AMaquinaTragamonedasEscuelaVieja::AMaquinaTragamonedasEscuelaVieja()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMaquinaTragamonedasEscuelaVieja::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaquinaTragamonedasEscuelaVieja::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaquinaTragamonedasEscuelaVieja::Initialize(int NumberOfDollars)
{
	//Spanw the No Dollars State and set this Slot Machine to it
	NoDollarsState = GetWorld()->SpawnActor<AEstadoSinDolares>(AEstadoSinDolares::StaticClass());
	NoDollarsState->SetSlotMachine(this);

	//Spanw the No Coin State and set this Slot Machine to it
	NoCoinState = GetWorld()->SpawnActor<AEstadoSinMonedas>(AEstadoSinMonedas::StaticClass());
	NoCoinState->SetSlotMachine(this);

	//Spanw the Coin Inserted State and set this Slot Machine to it
	CoinInsertedState = GetWorld()->SpawnActor<AEstadoMonedaInsertada>(AEstadoMonedaInsertada::StaticClass());
	CoinInsertedState->SetSlotMachine(this);

	//Spanw the Won Dollars State and set this Slot Machine to it
	WonDollarsState = GetWorld()->SpawnActor<AEstadoGanoDolares>(AEstadoGanoDolares::StaticClass());
	WonDollarsState->SetSlotMachine(this);

	//Set the amount of dollars
	Count = NumberOfDollars;
	//If its greater than 0, set the current State to No Coin State
	if (NumberOfDollars > 0) {
		State = NoCoinState;
	}
	else {
		State = NoDollarsState;
	}
}
void AMaquinaTragamonedasEscuelaVieja::InsertCoin()
{
	//Execute the Insert Coin routine based on the current state
	State->InsertCoin();
}
void AMaquinaTragamonedasEscuelaVieja::RejectCoin()
{
	//Execute the Reject Coin routine based on the current state
	State->RejectCoin();
}
void AMaquinaTragamonedasEscuelaVieja::PullLever()
{
	//Execute the Pull Lever and Payout routine based on the current state
	State->PullLever();
	State->Payout();
}
void AMaquinaTragamonedasEscuelaVieja::EmitDollars()
{
	//You won!
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Haz que llueva!"));
	
	//If the Slot Machine still have some dollars, decrease them by 50
	if (Count != 0) {
		Count = Count - 50;
	}
}
int AMaquinaTragamonedasEscuelaVieja::GetCount()
{
	//Returns the Dollars count
	return Count;
}
void AMaquinaTragamonedasEscuelaVieja::RestockDollars(int myCount)
{
	//Add the passed count to the Dollars amount and log it
	Count += myCount;
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("La máquina tragamonedas de la vieja escuela se acaba de llenar y el nuevo conteo de dólares es : % i"), Count));
	
	//Then execute the Restock Dollars routine based on the current state
	State->RestockDollars();
}

void AMaquinaTragamonedasEscuelaVieja::SetState(IEstado* myState)
{
	//Set the current state to the passed one
	State = myState;
}

IEstado* AMaquinaTragamonedasEscuelaVieja::GetState()
{
	//Returns the Current State
	return State;
}

IEstado* AMaquinaTragamonedasEscuelaVieja::GetNoDollarsState()
{
	//Returns the No Dollars State
	return NoDollarsState;
}

IEstado* AMaquinaTragamonedasEscuelaVieja::GetNoCoinState()
{
	//Returns the No Coin State
	return NoCoinState;
}

IEstado* AMaquinaTragamonedasEscuelaVieja::GetCoinInsertedState()
{
	//Returns the Coin Inserted State
	return CoinInsertedState;
}

IEstado* AMaquinaTragamonedasEscuelaVieja::GetWonDollarsState()
{
	//Returns the Won Dollars State
	return WonDollarsState;
}

FString AMaquinaTragamonedasEscuelaVieja::GetCurrentState()
{
	//Returns the 'Name' of current State
	return "Estado actual de la máquina tragamonedas :" + State->ToString();

}
