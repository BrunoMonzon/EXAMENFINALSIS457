// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EstadoEscenario.h"
#include "Escenario.generated.h"

UCLASS()
class TETRIS_UE4_API AEscenario : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEscenario();//Constructor

private:

	IEstadoEscenario* EstadoNeon;//Interfaz de estado del escenario
	IEstadoEscenario* EstadoPixel;//Interfaz de estado del escenario
	IEstadoEscenario* EstadoTech;//Interfaz de estado del escenario
	IEstadoEscenario* Estado;//Interfaz de estado del escenario

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* MeshEscenario;//Mesh del escenario

	UMaterialInterface* materialEscenarioNeon;//Material del escenario

	AEscenario* iniciar();//Funcion para iniciar el escenario
	void cambiarEscenario(AEscenario* _Escenario);//Funcion para cambiar el escenario
	void cambiarEstado(IEstadoEscenario* _Estado);//Funcion para cambiar el estado del escenario

	IEstadoEscenario* getEstadoNeon();//Metodos getter que permiten el cambio de estado del escenario (obtienen)
	IEstadoEscenario* getEstadoPixel();//Funcion para obtener el estado del escenario
	IEstadoEscenario* getEstadoTech();//Funcion para obtener el estado del escenario
	IEstadoEscenario* getEstado();//Funcion para obtener el estado del escenario
};
