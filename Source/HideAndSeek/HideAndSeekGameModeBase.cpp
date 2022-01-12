// Copyright Epic Games, Inc. All Rights Reserved.


#include "HideAndSeekGameModeBase.h"
#include "HideandSeekGameState.h"
#include "Kismet/GameplayStatics.h"

AHideAndSeekGameModeBase::AHideAndSeekGameModeBase()
{
    GameTimeMinutes = 5;
    bUseSeamlessTravel = true;
}

void AHideAndSeekGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}

void AHideAndSeekGameModeBase::StartGameCounting()
{
    GetWorldTimerManager().SetTimer(FullTimeHanle,this, &AHideAndSeekGameModeBase::TimeEnded, GameTimeMinutes * 60 + 1);
    GetWorldTimerManager().SetTimer(TimeCounter, this, &AHideAndSeekGameModeBase::TimerCountFunc,1,true);
}

void AHideAndSeekGameModeBase::TimerCountFunc()
{
   AHideandSeekGameState* GS = Cast<AHideandSeekGameState>(GetWorld()->GetGameState());
   if (GS)
   {
       const int CurrentTime = GetWorldTimerManager().GetTimerElapsed(FullTimeHanle);
       GS->CurrentTime = CurrentTime;
   }
}

void AHideAndSeekGameModeBase::TimeEnded()
{
    GetWorldTimerManager().ClearTimer(TimeCounter);
    //Hiders Win
    GameFinished(EWinner::Hider);
}

void AHideAndSeekGameModeBase::HiderCaught(APawn* Hider)
{
    auto GS= GetGameState<AHideandSeekGameState>();
    if(GS)
    {
        GS->Hiders.Remove(Hider);
        if (GS->Hiders.Num()<=0)
        {
            //ALL HIDER CAUGHT
            //Seeker Win
            GameFinished(EWinner::Seeker);
        }
    }
}

void AHideAndSeekGameModeBase::GameFinished(EWinner Winner)
{
    TArray<AActor*> PCs;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerControllerBase::StaticClass(),PCs);
    for (auto playerCtrl : PCs)
    {
        APlayerControllerBase* PCBase = Cast<APlayerControllerBase>(playerCtrl);
        if (PCBase)
        {
            PCBase->GameFinished(Winner, WinUIClass);
        }
    }
}

void AHideAndSeekGameModeBase::BackToMainMenu()
{
    GetWorldTimerManager().ClearTimer(FullTimeHanle);
    GetWorldTimerManager().ClearTimer(TimeCounter);
    GetWorld()->ServerTravel("/Game/HideAndSeek_main_menu");
}


