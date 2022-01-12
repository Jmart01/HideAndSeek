// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "CharacterBase.h"
#include "DefaultSpectatorPawn.h"
#include "HideAndSeekGameModeBase.h"
#include "WinUI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void APlayerControllerBase::GameFinished_Implementation(EWinner Winner, TSubclassOf<UWinUI> UI)
{
    //get rid of current ui
    ACharacterBase* CurrentPawn = Cast<ACharacterBase>(GetPawn());
    if (CurrentPawn)
    {
        CurrentPawn->DestroyUI();
    }
    ADefaultSpectatorPawn* CurrentSpectatorPawn = Cast<ADefaultSpectatorPawn>(GetPawn());
    if (CurrentSpectatorPawn && CurrentSpectatorPawn->JoiningWidget)
    {
        CurrentSpectatorPawn->JoiningWidget->RemoveFromParent();
    }
    
    //spawn new ui:
   WinUI = Cast<UWinUI>(CreateWidget(this,UI));
    if (WinUI)
    {
        WinUI->AddToViewport();
        WinUI->SetWiner(Winner);
        SetInputMode(FInputModeGameAndUI());
    }
}

void APlayerControllerBase::BackToMainMenu_Implementation()
{
    AHideAndSeekGameModeBase* GM = Cast<AHideAndSeekGameModeBase>( GetWorld()->GetAuthGameMode());
    if (GM&&HasAuthority())
    {
        WinUI->RemoveFromParent();
        GM->BackToMainMenu();    
    }
}

bool APlayerControllerBase::BackToMainMenu_Validate()
{
    return true;
}

void APlayerControllerBase::SetModeUIOnly()
{
    SetInputMode(FInputModeGameAndUI());
    bShowMouseCursor = true; 
}

void APlayerControllerBase::SetModeGameOnly()
{
    SetInputMode(FInputModeGameOnly());
    bShowMouseCursor = false;
}
