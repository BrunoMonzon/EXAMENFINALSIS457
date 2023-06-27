// Fill out your copyright notice in the Description page of Project Settings.


#include "EstadoMonedaInsertada.h"
#include "MaquinaTragamonedasEscuelaVieja.h"

// Sets default values
AEstadoMonedaInsertada::AEstadoMonedaInsertada()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEstadoMonedaInsertada::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEstadoMonedaInsertada::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstadoMonedaInsertada::SetSlotMachine(AMaquinaTragamonedasEscuelaVieja* SlotMachine)
{
	//Set the Slot Machine of this state
	OldSchoolSlotMachine = SlotMachine;
}
void AEstadoMonedaInsertada::InsertCoin()
{
	//Log the Insert Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("No puedes insertar otra moneda de casino"));
}
void AEstadoMonedaInsertada::RejectCoin()
{
	//Log the Reject Coin string and set the state to "No Coin State"
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Moneda de casino devuelta"));

	OldSchoolSlotMachine->SetState(OldSchoolSlotMachine -> GetNoCoinState());
}
void AEstadoMonedaInsertada::PullLever()
{
	//Log the Pull Lever string and set the state to "Won Dollars State"
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Tiraste de la palanca..."));

	OldSchoolSlotMachine->SetState(OldSchoolSlotMachine -> GetWonDollarsState());
}
void AEstadoMonedaInsertada::Payout()
{
	//Log the Payout string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("No se dispensan dólares"));
}
void AEstadoMonedaInsertada::RestockDollars() { /*Nothing*/ }

FString AEstadoMonedaInsertada::ToString()
{
	//Return the String of this state
	return "esperando el tirón de la palanca";
}