// Fill out your copyright notice in the Description page of Project Settings.


#include "JoiningWidget.h"
#include "DefaultSpectatorPawn.h"
#include "HideandSeekGameState.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameInstance.h"
void UJoiningWidget::NativeConstruct()
{
    SeekerBtn->OnClicked.AddDynamic(this, &UJoiningWidget::SeekerBtnClicked);
    HiderBtn->OnClicked.AddDynamic(this, &UJoiningWidget::HiderBtnClicked);
    TArray<AActor*> AllPawns;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),SeekerRoleType.Get(),AllPawns);
    if(AllPawns.Num()>0)
    {
        SeekerBtn->SetIsEnabled(false);   
    }        
}

void UJoiningWidget::SeekerBtnClicked()
{
    if(GetOwningLocalPlayer() && GetOwningLocalPlayer()->GetPlayerController(GetWorld()))
    {
        ADefaultSpectatorPawn* Pawn = Cast<ADefaultSpectatorPawn>(GetOwningLocalPlayer()->GetPlayerController(GetWorld())->GetPawn());
        if (Pawn)
        {
            Pawn->StartsPlay(SeekerRoleType,true);
            RemoveFromParent();
        }
    }
}

void UJoiningWidget::HiderBtnClicked()
{
    if(GetOwningLocalPlayer() && GetOwningLocalPlayer()->GetPlayerController(GetWorld()))
    {
        ADefaultSpectatorPawn* Pawn = Cast<ADefaultSpectatorPawn>(GetOwningLocalPlayer()->GetPlayerController(GetWorld())->GetPawn());
        if (Pawn)
        {
            Pawn->StartsPlay(HiderRoleType);
            RemoveFromParent();
        }
    }
}

