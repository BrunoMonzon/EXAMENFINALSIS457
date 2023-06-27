// Fill out your copyright notice in the Description page of Project Settings.


#include "EstadoTech.h"
#include "Escenario.h"

// Sets default values
AEstadoTech::AEstadoTech()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    materialEscenarioNeon = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Blueprints/noche_paisaje_Mat.noche_paisaje_Mat'"));//se carga el material del escenario
}

// Called when the game starts or when spawned
void AEstadoTech::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEstadoTech::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstadoTech::EstablecerEscenario(AEscenario* _Escenario)//funcion para establecer el escenario
{
   
    FTransform SpawnLocation;//se establece la posicion del escenario
   
    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Estado Tech"));//mensaje de debug
   
    _Escenario->MeshEscenario->SetMaterial(0, materialEscenarioNeon);//se establece el material del escenario

    
    Escenario->cambiarEstado(Escenario->getEstadoNeon());//se cambia el estado del escenario get(obtener)
}

void AEstadoTech::SetEscenario(AEscenario* _Escenario)//funcion para establecer el escenario
{
	Escenario = _Escenario;//se establece el escenario
}

