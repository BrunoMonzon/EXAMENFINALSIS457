// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EstadoEscenario.h"
#include "EstadoNeon.generated.h"

UCLASS()
class TETRIS_UE4_API AEstadoNeon : public AActor , public IEstadoEscenario//hereda de interfaz 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEstadoNeon();//Constructor

private:

	UPROPERTY()
		class AEscenario* Escenario;

	UMaterialInterface* materialEscenarioManana;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void EstablecerEscenario(class AEscenario* _Escenario) override;//Funcion para establecer el escenario, override para sobreescribir la funcion
	virtual void SetEscenario(class AEscenario* _Escenario) override;//Funcion para establecer el escenario
};
