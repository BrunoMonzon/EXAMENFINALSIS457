// Fill out your copyright notice in the Description page of Project Settings.


#include "EstadoNeon.h"
#include "Escenario.h"

// Sets default values
AEstadoNeon::AEstadoNeon()//Constructor
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    materialEscenarioManana = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Blueprints/paisaje_de_dia_Mat.paisaje_de_dia_Mat'"));
    //BlockMesh->SetMaterial(0, materialEsfera);

}

// Called when the game starts or when spawned
void AEstadoNeon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEstadoNeon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstadoNeon::EstablecerEscenario(AEscenario* _Escenario)//Funcion que establece el escenario
{
    //Escenario->Destroy();
    //FTransform SpawnLocation;
    //UPROPERTY()
        //AEscenario* B;
    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Estado Neon"));//mensaje de debug
    //Escenario = GetWorld()->SpawnActor<AEscenario>(AEscenario::StaticClass(), SpawnLocation);
    //AEscenario* B = GetWorld()->SpawnActor<AEscenarioPiedras>(this->GetActorLocation(), Rotation);
    _Escenario->MeshEscenario->SetMaterial(0, materialEscenarioManana);//se establece el material del escenario

    //B->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
    //Escenario->SetActorRelativeLocation(FVector(260.0, -25.0, 100.0));
    //Escenario->SetActorRelativeRotation(FRotator(0.0, 90.0, 90.0));*/

    Escenario->cambiarEstado(Escenario->getEstadoPixel());//se cambia el estado del escenario get(obtener)

}

void AEstadoNeon::SetEscenario(AEscenario* _Escenario)//Funcion que establece el escenario set(establecer)
{
	Escenario = _Escenario;//se establece el escenario
}

