// Fill out your copyright notice in the Description page of Project Settings.


#include "EstadoGanoDolares.h"
#include "MaquinaTragamonedasEscuelaVieja.h"

// Sets default values
AEstadoGanoDolares::AEstadoGanoDolares()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEstadoGanoDolares::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEstadoGanoDolares::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstadoGanoDolares::SetSlotMachine(AMaquinaTragamonedasEscuelaVieja* SlotMachine)
{
	//Set the Slot Machine of this state
	OldSchoolSlotMachine = SlotMachine;
}

void AEstadoGanoDolares::InsertCoin()
{
	//Log the Insert Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Por favor espere, la máquina está entregando dólares"));
}
void AEstadoGanoDolares::RejectCoin()
{
	//Log the Reject Coin string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("Cálmate, ya tiraste de la palanca"));
}
void AEstadoGanoDolares::PullLever()
{
	//Log the Pull Lever string
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("¡No tire de la palanca dos veces!"));
}
void AEstadoGanoDolares::Payout()
{
	//Payout time! Emit the dollars from the Slot Machine
	OldSchoolSlotMachine->EmitDollars();
	if (OldSchoolSlotMachine->GetCount() > 0)
	{
		//If the Slot Machine still have dollars, set its state to No Coin State
		OldSchoolSlotMachine->SetState(OldSchoolSlotMachine -> GetNoCoinState());
	}
	else
	{
		//If the Slot Machine doesn't have any dollars left, log it and set its state to No Dollars State
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("La máquina ahora no tiene efectivo"));
		OldSchoolSlotMachine->SetState(OldSchoolSlotMachine -> GetNoDollarsState());
	}
}
void AEstadoGanoDolares::RestockDollars() { /*Nothing*/ }

FString AEstadoGanoDolares::ToString()
{
	//Return the String of this state
	return "entregando efectivo";
}
