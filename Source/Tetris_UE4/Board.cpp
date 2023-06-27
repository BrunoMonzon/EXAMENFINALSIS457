// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Escenario.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ABoard::ABoard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<USoundCue> LineRemove_Sound(TEXT("SoundCue'/Game/Sounds/line-remove_Cue.line-remove_Cue'"));//cargar el sonido de la linea
    if(LineRemove_Sound.Succeeded())
    {
        LineRemoveSoundCue = LineRemove_Sound.Object;//asignar el sonido de la linea
    }
    
    static ConstructorHelpers::FObjectFinder<USoundCue> MoveToEnd_Sound(TEXT("SoundCue'/Game/Sounds/force-hit_Cue.force-hit_Cue'"));//cargar el sonido de la linea
    if(MoveToEnd_Sound.Succeeded())
    {
        MoveToEndSoundCue = MoveToEnd_Sound.Object;
    }
    
    static ConstructorHelpers::FObjectFinder<USoundCue> GameStart_Sound(TEXT("SoundCue'/Game/Sounds/start_Cue.start_Cue'"));
    if(GameStart_Sound.Succeeded())
    {
        GameStartSoundCue = GameStart_Sound.Object;
    }
    
    static ConstructorHelpers::FObjectFinder<USoundCue> GameOver_Sound(TEXT("SoundCue'/Game/Sounds/gameover_Cue.gameover_Cue'"));
    if(GameOver_Sound.Succeeded())
    {
        GameOverSoundCue = GameOver_Sound.Object;
    }
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();

    Escenario = GetWorld()->SpawnActor<AEscenario>(AEscenario::StaticClass());//spawnear el escenario
    Escen = Escenario->iniciar();//iniciar el escenario
    
    //Escenario->cambiarEscenario();
    //Escenario->cambiarEscenario();
    //Escenario->cambiarEscenario();
	
    for(TActorIterator<APieces> it(GetWorld()); it; ++it)//destruir las piezas que estan en el tablero
    {

        if(it->GetFName() == TEXT("DissmissPieces"))//si el nombre de la pieza es DissmissPieces
        {
            it->Dismiss();
            it->Destroy();
        }
    }
}

// Called every frame
void ABoard::Tick(float DeltaTime)//verifica que cuando la pieza llega al fondo se va a generar las nuevas piezas
{
    Super::Tick(DeltaTime);//se llama a la funcion de la clase padre

    if (bGameOver)//si el juego termino
    {
        return;//se sale de la funcion
    }

    switch (Status)
    {
    case PS_NOT_INITED:

        Inicio();//se llamada a la funcion inicio 
        // NewPiece();
        CoolLeft = CoolDown;
        Status = PS_MOVING;
        break;
    case PS_MOVING:
        CoolLeft -= DeltaTime;
        if (CoolLeft <= 0.0f)
        {
            MoveDown();
        }
        break;
    case PS_GOT_BOTTOM://si la pieza llego al fondo

        New->Eliminar();//se llama a la funcion eliminar, elimina su representacion fisica 
        NewNew->Eliminar();//se llama a la funcion eliminar
        CoolLeft -= DeltaTime;//se resta el tiempo
        if (CoolLeft <= 0.0f)//si el tiempo es menor a 0
        {
            if (CurrentPieces)//si la pieza actual existe
            {
                CurrentPieces->Dismiss();//se llama a la funcion dismiss
                CurrentPieces->Destroy();//se destruye el actor
            }
            CurrentPieces = nullptr;//se asigna null a la pieza actual

            NewPieces();//se llama a la funcion newpiece modificada
            CoolLeft = CoolDown;//se asigna el tiempo de cooldown
            Status = PS_MOVING;//se asigna el estado de moving
        }
        break;//se sale del switch
    default://si no se cumple ninguno de los casos anteriores
        break;//se sale del switch
    }
}

// Called to bind functionality to input
void ABoard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Rotate", IE_Pressed, this, &ABoard::Rotate);
    PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ABoard::MoveLeft);
    PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ABoard::MoveRight);
    PlayerInputComponent->BindAction("MoveDownToEnd", IE_Pressed, this, &ABoard::MoveDownToEnd);
    //PlayerInputComponent->BindAction("NewPieces", IE_Pressed, this, &ABoard::NewPieces);
    //PlayerInputComponent->BindAction("CheckLine", IE_Pressed, this, &ABoard::CheckLine);
}

void ABoard::Rotate()
{
    if(CurrentPieces && Status != PS_GOT_BOTTOM)
    {
        CurrentPieces->TestRotate();
    }
}

void ABoard::MoveLeft()
{
    if(CurrentPieces)
    {
        CurrentPieces->MoveLeft();
        if(Status == PS_GOT_BOTTOM)
        {
            MoveDownToEnd();
        }
    }
}

void ABoard::MoveRight()
{
    if(CurrentPieces)
    {
        CurrentPieces->MoveRight();
        if(Status == PS_GOT_BOTTOM)
        {
            MoveDownToEnd();
        }
    }
}
void ABoard::Inicio()//funcion inicio
{
    FVector Loca(0.0, 100.0, 100.0);//se crea un vector
    FVector Loc(0.0, 100.0, 195.0);//son 3 vectores de locacion
    FVector Location(0.0, 5.0, 195.0);//tienen que tener distintas locaciones para que se generen en distintos lugares
    FRotator Rotation(0.0, 0.0, 0.0);
    NewNew = GetWorld()->SpawnActor<APieces>(Loca, Rotation);//se crea un nuevo actor
    NewNew->Index();//se llama a la funcion index 
    NewNew->SpawnBlocks();//se llama a la funcion spawnblocks
    New = GetWorld()->SpawnActor<APieces>(Loc, Rotation);//se crea un nuevo actor
    New->Index();//se llama a la funcion index para sacar un numero aleatorio 
    New->SpawnBlocks();//se llama a la funcion spawnblocks dependiendo al numer o queha salido 
    CurrentPieces = GetWorld()->SpawnActor<APieces>(Location, Rotation);////se crea un nuevo actor
   CurrentPieces->Index();//se llama a la funcion index
   CurrentPieces->SpawnBlocks();//se llama a la funcion spawnblocks
}

void ABoard::MoveDown()
{
    if(CurrentPieces)
    {
        if(!CurrentPieces->MoveDown())
        {
            Status = PS_GOT_BOTTOM;
        }
        CoolLeft = CoolDown;
    }
}

void ABoard::NewPieces()
{
    CheckLine();//se llama a la funcion checkline
    FVector Loca(0.0, 100.0, 100.0);//tiene los 3 vectores de locacion 
    FVector Location(0.0, 5.0, 195.0);//se crea un vector
    FVector Loc(0.0, 100.0, 195.0);
    FRotator Rotation(0.0, 0.0, 0.0);
    if (CurrentPieces)//si la pieza actual existe
    {
        CurrentPieces->Dismiss();//se llama a la funcion dismiss
        CurrentPieces->Destroy();//se destruye el actor
    }

    int der = New->getIndex();//se obtiene el index de la pieza anterior 

    CurrentPieces = GetWorld()->SpawnActor<APieces>(Location, Rotation);//se crea un nuevo actor
    CurrentPieces->setIndex(der);//se asigna el index se le mete el index del anterior 
    CurrentPieces->SpawnBlocks();//se llama a la funcion spawnblocks
    if (New)//si la pieza new existe, crea la pieza siguiente
    {
        New->Dismiss();//
        New->Destroy();

    }

    int dere = NewNew->getIndex();//se obtiene el index de la pieza
    New = GetWorld()->SpawnActor<APieces>(Loc, Rotation);//se crea un nuevo actor
    New->setIndex(dere);//se asigna el index
    //New->Index();
    New->SpawnBlocks();//se llama a la funcion spawnblocks
    if (NewNew)//si la pieza newnew existe
    {
        NewNew->Dismiss();//se llama a la funcion dismiss
        NewNew->Destroy();//destruye 

    }
    NewNew = GetWorld()->SpawnActor<APieces>(Loca, Rotation);//se crea un nuevo actor
    NewNew->Index();//se llama a la funcion index, como es ultimo genera un nuevo index
    NewNew->SpawnBlocks();//se llama a la funcion spawnblocks
    bGameOver = CheckGameOver();//se llama a la funcion checkgameover
    if (bGameOver)//si el juego termino 
    {
        UE_LOG(LogTemp, Warning, TEXT("Game Over!!!!!!!!"));
        /*if (GameOverSoundCue)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), GameOverSoundCue, GetActorLocation(), GetActorRotation());
        }*/
    }
}

void ABoard::CheckLine()//comrpobar si hay lineas 
{
    auto MoveDownFromLine = [this](int z){//mover las piezas hacia abajo
        FVector Location(0.0f, 0.0f, 5.0*z + 100.0);//posicion de las piezas
        FRotator Rotation(0.0f, 0.0f, 0.0f);//rotacion de las piezas
        TArray<struct FOverlapResult> OutOverlaps;//array de los overlaps
        FCollisionShape CollisionShape;
        FVector Extent(4.5f, 49.5f, 95.0+4.5-5.0*z);
        CollisionShape.SetBox(Extent);
        DrawDebugBox(GetWorld(), Location, Extent, FColor::Purple, false, 1, 0, 1);
        FCollisionQueryParams Params;
        FCollisionResponseParams ResponseParam;
        if(GetWorld()->OverlapMultiByChannel(OutOverlaps,
            Location, Rotation.Quaternion(), ECollisionChannel::ECC_WorldDynamic,
            CollisionShape, Params, ResponseParam))
        {
            for(auto&& Result: OutOverlaps)
            {
                FVector NewLocation = Result.GetActor()->GetActorLocation();
                NewLocation.Z -= 10.0f;
                Result.GetActor()->SetActorLocation(NewLocation);
            }
        }
    };
    
    int z = 0;
    while(z < 20)
    {
        FVector Location(0.0f, 0.0f, 10.0f * z + 5.0f);
        FRotator Rotation(0.0f, 0.0f, 0.0f);
        TArray<struct FOverlapResult> OutOverlaps;
        FCollisionShape CollisionShape;
        CollisionShape.SetBox(FVector(4.0f, 49.0f, 4.0f));
        //DrawDebugBox(GetWorld(), Location, FVector(4.5f, 49.5f, 4.5f), FColor::Purple, false, 1, 0, 1);
        FCollisionQueryParams Params;
        FCollisionResponseParams ResponseParam;
        bool b = GetWorld()->OverlapMultiByChannel(OutOverlaps,
            Location, Rotation.Quaternion(), ECollisionChannel::ECC_WorldDynamic,
            CollisionShape, Params, ResponseParam);//comprobar si hay colisiones
        if(!b || OutOverlaps.Num() < 10)//si no hay colisiones o hay menos de 10
        {
            ++z;//comprobar la siguiente linea
            continue;
        }
        else // si la  fila de piezas esta llena de bloques se destruye la linea 
        {   
            UE_LOG(LogTemp, Warning, TEXT("Find FULL LINE at z=%d"), z);//mensaje de encontrar linea llena
            for(auto&& Result: OutOverlaps)//para cada pieza de la linea llena de piezas destruir 
            {
                Result.GetActor()->Destroy();//destruir pieza
            }
            MoveDownFromLine(z);//mover las piezas de arriba hacia abajo
            NumFilasDest += 1;//aumentar el numero de filas destruidas
            //debugmessage 
            GEngine->AddOnScreenDebugMessage (-1, 5.f, FColor::Orange, FString::Printf(TEXT("Num de filas completadas: %d"), NumFilasDest));//mostrar el numero de filas destruidas
            NumBloquesDest += 10;//aumentar el numero de bloques destruidos            
            GEngine->AddOnScreenDebugMessage (-1, 5.f, FColor::Orange, FString::Printf(TEXT("Num de bloques destruidos: %d"), NumBloquesDest));//mostrar el numero de bloques destruidos
            Puntaje += 100;//aumentar el puntaje
            GEngine->AddOnScreenDebugMessage (-1, 5.f, FColor::Orange, FString::Printf(TEXT("Puntaje: %d"), Puntaje));//mostrar el puntaje

            Escenario->cambiarEscenario(Escen);//CAMBIAR ESCENARIO 
            
            if(LineRemoveSoundCue)//sonido de linea eliminada
            {
                UGameplayStatics::PlaySoundAtLocation(GetWorld(), LineRemoveSoundCue, GetActorLocation(), GetActorRotation());//reproducir sonido
            }
        }
    }
}

void ABoard::MoveDownToEnd()
{
    if(!CurrentPieces)
    {
        return;
    }
    
    while(CurrentPieces->MoveDown())
    {
    }
    
    if(MoveToEndSoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), MoveToEndSoundCue, GetActorLocation(), GetActorRotation());
    }
    
    switch(Status)
    {
        case PS_MOVING:
            Status = PS_GOT_BOTTOM;
            CoolLeft = CoolDown;
            break;
        case PS_GOT_BOTTOM:
            break;
        default:
            UE_LOG(LogTemp, Warning, TEXT("Wrong status for MoveDownToEnd"));
            break;
    }
}

bool ABoard::CheckGameOver()
{
    if(!CurrentPieces)
    {
        UE_LOG(LogTemp, Warning, TEXT("NoPieces"));
        return true;
    }
    
    return CurrentPieces->CheckWillCollision([](FVector OldVector){ return OldVector; });
}
