// Fill out your copyright notice in the Description page of Project Settings.


#include "Escenario.h"
#include "EstadoEscenario.h"
#include "EstadoNeon.h"
#include "EstadoPixel.h"
#include "EstadoTech.h"

// Sets default values
AEscenario::AEscenario()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshEscenario = CreateDefaultSubobject<UStaticMeshComponent>("Escenario Mesh");
    RootComponent = MeshEscenario;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> Escenarios(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));
    //StaticMesh'/Game/Mesh/block.block'
    if (Escenarios.Succeeded())
    {
        MeshEscenario->SetStaticMesh(Escenarios.Object);
        MeshEscenario->SetRelativeLocation(FVector(1000.0f, 1000.0f, 1000.0f));
        MeshEscenario->SetWorldScale3D(FVector(5.0f, 3.0f, 2.5f));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("mesh not found"));
    }

    materialEscenarioNeon = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Blueprints/tetris_Mat.tetris_Mat'"));
}

// Called when the game starts or when spawned
void AEscenario::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEscenario::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AEscenario* AEscenario::iniciar()//funcion para iniciar el escenario
{
    EstadoNeon = GetWorld()->SpawnActor<AEstadoNeon>(AEstadoNeon::StaticClass());//se crea el estado neon
   
    EstadoNeon->SetEscenario(this);//se establece el escenario

    //Spanw the No Coin State and set this Slot Machine to it
    EstadoPixel = GetWorld()->SpawnActor<AEstadoPixel>(AEstadoPixel::StaticClass());//se crea el estado pixel
    EstadoPixel->SetEscenario(this);//se establece el escenario set(establecer)

    //Spanw the Coin Inserted State and set this Slot Machine to it
    EstadoTech = GetWorld()->SpawnActor<AEstadoTech>(AEstadoTech::StaticClass());//se crea el estado tech
    EstadoTech->SetEscenario(this);//se establece el escenario


    FTransform SpawnLocation;
   
    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, TEXT("Modalidad Clasica"));//mensaje de debug
    AEscenario* Escenario = GetWorld()->SpawnActor<AEscenario>(AEscenario::StaticClass(), SpawnLocation);//se crea el escenario
    
    Escenario->MeshEscenario->SetMaterial(0, materialEscenarioNeon);//se establece el material del escenario

    
    Escenario->SetActorRelativeLocation(FVector(260.0, -25.0, 100.0));//se establece la posicion del escenario
    Escenario->SetActorRelativeRotation(FRotator(0.0, 90.0, 90.0));//se establece la rotacion del escenario

    Estado = EstadoNeon;//se establece el estado del escenario
    return Escenario;//se retorna el escenario
}

void AEscenario::cambiarEscenario(AEscenario* _Escenario)//funcion para cambiar el escenario
{
    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Modalidad Futurista: Escenario nuevo"));//mensaje de debug
    Estado->EstablecerEscenario(_Escenario);//se establece el escenario
}

void AEscenario::cambiarEstado(IEstadoEscenario* _Estado)//funcion para cambiar el estado del escenario
{
    Estado = _Estado;//se establece el estado del escenario
}

IEstadoEscenario* AEscenario::getEstadoNeon()//funcion para obtener el estado neon
{
    return EstadoNeon;//se retorna el estado neon
}

IEstadoEscenario* AEscenario::getEstadoPixel()//funcion para obtener el estado pixel
{
    return EstadoPixel;//se retorna el estado pixel
}

IEstadoEscenario* AEscenario::getEstadoTech()//funcion para obtener el estado tech
{
    return EstadoTech;//se retorna el estado tech
}

IEstadoEscenario* AEscenario::getEstado()//funcion para obtener el estado del escenario
{
    return Estado;//se retorna el estado del escenario
}

