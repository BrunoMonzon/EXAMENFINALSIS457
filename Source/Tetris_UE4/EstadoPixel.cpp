// Fill out your copyright notice in the Description page of Project Settings.


#include "EstadoPixel.h"
#include "Escenario.h"

// Sets default values
AEstadoPixel::AEstadoPixel()//CONSTRUCTOR
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;//

    materialEscenarioManana = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Blueprints/atardecer_paisaje_Mat.atardecer_paisaje_Mat'"));//CARGA EL MATERIAL DEL ESCENARIO

}

// Called when the game starts or when spawned
void AEstadoPixel::BeginPlay()//FUNCION QUE SE EJECUTA AL INICIAR EL JUEGO
{
	Super::BeginPlay();//LLAMA A LA FUNCION DE LA CLASE PADRE
	
}

// Called every frame
void AEstadoPixel::Tick(float DeltaTime)//FUNCION QUE SE EJECUTA EN CADA FRAME
{
	Super::Tick(DeltaTime);//LLAMA A LA FUNCION DE LA CLASE PADRE

}

void AEstadoPixel::EstablecerEscenario(class AEscenario* _Escenario)//FUNCION QUE ESTABLECE EL ESCENARIO
{

    FTransform SpawnLocation;//VARIABLE QUE GUARDA LA POSICION DEL ESCENARIO

    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Estado Pixel"));//MUESTRA UN MENSAJE EN PANTALLA

 
    _Escenario->MeshEscenario->SetMaterial(0, materialEscenarioManana);//SE ESTABLECE EL MATERIAL DEL ESCENARIO

    
    Escenario->cambiarEstado(Escenario->getEstadoTech());//SE CAMBIA EL ESTADO DEL ESCENARIO GET(OBTENER)
}

void AEstadoPixel::SetEscenario(AEscenario* _Escenario)//FUNCION QUE ESTABLECE EL ESCENARIO
{
	Escenario = _Escenario;//SE ESTABLECE EL ESCENARIO
}

