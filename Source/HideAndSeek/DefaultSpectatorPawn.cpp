// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultSpectatorPawn.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "CharacterBase.h"
#include "HideAndSeekGameModeBase.h"
#include "HideandSeekGameState.h"

void ADefaultSpectatorPawn::BeginPlay()
{
    Super::BeginPlay();
    if(JoingWidgetType)
    {
        APlayerController* pc =Cast<APlayerController>(GetController());
        auto widget = CreateWidget(pc,JoingWidgetType);
        if (widget)
        {
            widget->AddToViewport();
            JoiningWidget = widget;
            FInputModeUIOnly UIOnly;
            pc->SetInputMode(UIOnly);
        }
    }
}

void ADefaultSpectatorPawn::StartsPlay_Implementation(TSubclassOf<ACharacterBase> PawnType, bool isSeeker)
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (PC)
    {
        FActorSpawnParameters SpawnParam;
        FTransform SpawnTransform = GetActorTransform();
        SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        APawn* NewPawn = Cast<APawn>(GetWorld()->SpawnActor(PawnType,&SpawnTransform,SpawnParam));
        if(NewPawn)
        {
            PC->Possess(NewPawn);
            AHideandSeekGameState* GameState = Cast<AHideandSeekGameState>(GetWorld()->GetGameState());
            if(GameState)
            {
                if(isSeeker)
                {
                    GameState->Seeker = NewPawn;
                    AHideAndSeekGameModeBase* GM = Cast<AHideAndSeekGameModeBase>(GetWorld()->GetAuthGameMode());
                    if (GM)
                    {
                        GM->StartGameCounting();
                    }
                }else
                {
                    GameState->Hiders.Add(NewPawn);
                    UE_LOG(LogTemp, Warning, TEXT("hiders in world %d"), GameState->Hiders.Num());
                }   
            }
        }
    }

}

bool ADefaultSpectatorPawn::StartsPlay_Validate(TSubclassOf<ACharacterBase> PawnType, bool isSeeker)
{
    return true;
}


