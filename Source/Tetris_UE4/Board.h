// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pieces.h"
#include "Escenario.h"
#include "Board.generated.h"

UCLASS()
class TETRIS_UE4_API ABoard : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;//para que el jugador pueda mover las piezas

    void Rotate(); 
    void MoveLeft(); 
    void MoveRight();
    void MoveDown();  
    void NewPieces(); 
    void CheckLine(); 
    void MoveDownToEnd(); 
    void Inicio();//es una funcion se usa una vez cuando inicia el juego para generar 3 piezas siguientes
public:

    int NumBloquesDest=0;//Numero de bloques destruidos
    int NumFilasDest=0;//Numero de filas destruidas
    int NumPiezasUtil=0;//Numero de piezas utilizadas
    int Puntaje=0;//Puntaje

    UPROPERTY()
    APieces* CurrentPieces;
    UPROPERTY()
    APieces* NewNew;//se declara un puntero de tipo pieza que se llama newnew
    APieces* New;//pieza actual
    
    UPROPERTY()
    class USoundCue* LineRemoveSoundCue;
    
    UPROPERTY()
    class USoundCue* MoveToEndSoundCue;
    
    UPROPERTY()
    class USoundCue* GameOverSoundCue;
    
    UPROPERTY()
    class USoundCue* GameStartSoundCue;

    UPROPERTY()
    AEscenario* Escenario;

    UPROPERTY()
    AEscenario* Escen;

private:
    enum PiecesStatus { PS_NOT_INITED, PS_MOVING, PS_GOT_BOTTOM};//PS_GOT_BOTTOM: cuando la pieza llega al fondo
    PiecesStatus Status = PS_NOT_INITED;//Estado de la pieza
    
    const float CoolDown = 0.5f;
    float CoolLeft = 0.5f;
    bool bGameOver = false;
    
    bool CheckGameOver();   
};
