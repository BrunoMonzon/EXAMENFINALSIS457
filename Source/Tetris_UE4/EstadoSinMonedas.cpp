// Fill out your copyright notice in the Description page of Project Settings.


#include "EstadoSinMonedas.h"
#include "MaquinaTragamonedasEscuelaVieja.h"

// Sets default values
AEstadoSinMonedas::AEstadoSinMonedas()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEstadoSinMonedas::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEstadoSinMonedas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstadoSinMonedas::SetSlotMachine(class AMaquinaTragamonedasEscuelaVieja* SlotMachine)
{
	//Set the Slot Machine of this state
	OldSchoolSlotMachine = SlotMachine;
}
void AEstadoSinMonedas::InsertCoin()
{
	//Log the Insert Coin string and set the state to "Coin Inserted State"
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Tu insertaste una moneda de Casino"));
	OldSchoolSlotMachine->SetState(OldSchoolSlotMachine -> GetCoinInsertedState()); // establece el estado de la máquina tragamonedas en el estado de moneda insertada
}

void AEstadoSinMonedas::RejectCoin()
{
	//Log the Reject Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Tu NO insertaste una moneda de Casino"));
}

void AEstadoSinMonedas::PullLever()
{
	//Log the Pull Lever string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Tu volviste, pero no hay una moneda de Casino"));
}

void AEstadoSinMonedas::Payout()
{
	//Log the Payout string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Tu necesitas pagar primero"));
}

void AEstadoSinMonedas::RestockDollars() { /*Nothing*/ }

FString AEstadoSinMonedas::ToString()
{
	//Return the String of this state
	return "Esperando por una moneda de casino";
}
