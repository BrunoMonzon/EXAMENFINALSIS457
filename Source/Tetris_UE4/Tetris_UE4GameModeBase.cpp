// Fill out your copyright notice in the Description page of Project Settings.


#include "Tetris_UE4GameModeBase.h"
#include "Board.h"
#include "MaquinaTragamonedasEscuelaVieja.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

ATetris_UE4GameModeBase::ATetris_UE4GameModeBase()
{
    DefaultPawnClass = ABoard::StaticClass();
}

void ATetris_UE4GameModeBase::BeginPlay()
{
    Super::BeginPlay();

    //Create the Slot Machine and set its Dollars Amount to 100
    /*AMaquinaTragamonedasEscuelaVieja* OldSchoolSlotMachine = GetWorld()->SpawnActor<AMaquinaTragamonedasEscuelaVieja>(AMaquinaTragamonedasEscuelaVieja::StaticClass());
    OldSchoolSlotMachine->Initialize(100);

    //Log the current Slot Machine state
    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s"), *OldSchoolSlotMachine->GetState() -> ToString()));
    //Insert coin and Pull the lever
    OldSchoolSlotMachine->InsertCoin();
    OldSchoolSlotMachine->PullLever();
    //Log the current Slot Machine state
    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s"), *OldSchoolSlotMachine->GetState() -> ToString()));
    //Insert coin, Pull the lever, then insert coin again
    OldSchoolSlotMachine->InsertCoin();
    OldSchoolSlotMachine->PullLever();
    OldSchoolSlotMachine->InsertCoin();
    //Log the current Slot Machine state
    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s"), *OldSchoolSlotMachine->GetState() -> ToString()));
    //Pull the lever
    OldSchoolSlotMachine->PullLever();
    //Add 100 Dollars
    OldSchoolSlotMachine->RestockDollars(100);
    //Insert coin and Pull the lever
    OldSchoolSlotMachine->InsertCoin();
    OldSchoolSlotMachine->PullLever();
    //Log the current Slot Machine state
    GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s"), *OldSchoolSlotMachine->GetState() -> ToString()));
    */
    
    for(TActorIterator<ACameraActor> it(GetWorld()); it; ++it)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Find camera: %s"), *(it->GetFName().ToString()));
        if(it->GetFName() == TEXT("BoardCamera"))
        {
            APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
            PC->SetViewTargetWithBlend(*it, 0.5);
            break;
        }
    }
}
