// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EstadoEscenario.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEstadoEscenario : public UInterface//Interfaz de estado del escenario
{
	GENERATED_BODY()
};

/**
 * 
 */
class TETRIS_UE4_API IEstadoEscenario//Interfaz de estado del escenario
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
		// AGREGRAR FUNCIONES VIRTUALES PURAS DE LA INTERFAZ. ESTA ES LA CLASE QUE SE HEREDARÁ PARA IMPLEMENTAR ESTA INTERFAZ.
public://Funciones virtuales puras de la interfaz
	//ESTAS FUNCIONES SE HEREDARAN A LOS ESTADOS NEON, PIXEL Y TECH
	virtual void EstablecerEscenario(class AEscenario* _Escenario) = 0;//Este método es el encargado de cambiar la apariencia del escenario.
	virtual void SetEscenario(class AEscenario* Escenario) = 0;//Este método tiene el parámetro Escenario que almacenalos 3 estados que puede tener el escenario.

};
