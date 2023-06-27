// Fill out your copyright notice in the Description page of Project Settings.


#include "EstadoSinDolares.h"
#include "MaquinaTragamonedasEscuelaVieja.h"

// Sets default values
AEstadoSinDolares::AEstadoSinDolares()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEstadoSinDolares::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEstadoSinDolares::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstadoSinDolares::SetSlotMachine(class AMaquinaTragamonedasEscuelaVieja* SlotMachine)
{
	//Set the Slot Machine of this state
	OldSchoolSlotMachine = SlotMachine;
}

void AEstadoSinDolares::InsertCoin()
{
	//Log the Insert Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("No puede insertar una moneda de casino, la máquina no tiene dinero"));
}

void AEstadoSinDolares::RejectCoin()
{
	//Log the Reject Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("No has insertado una moneda de casino"));
}

void AEstadoSinDolares::PullLever()
{
	//Log the Pull Lever string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Te diste la vuelta, pero NO hay dinero en la máquina"));
}

void AEstadoSinDolares::Payout()
{
	//Log the Payout string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("No se pagó dinero"));
}

void AEstadoSinDolares::RestockDollars()
{
	//Set the state to "No Coin State"
	OldSchoolSlotMachine->SetState(OldSchoolSlotMachine -> GetNoCoinState()); // establece el estado de la máquina tragamonedas en el estado de moneda insertada
}

FString AEstadoSinDolares::ToString()
{
	//Return the String of this state
	return "la máquina no tiene efectivo";
}
