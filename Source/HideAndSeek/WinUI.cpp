// Fill out your copyright notice in the Description page of Project Settings.


#include "WinUI.h"

#include "Kismet/GameplayStatics.h"


void UWinUI::NativeConstruct()
{
    PlayAgainBtn->OnClicked.AddDynamic(this, &UWinUI::PlayAgainBtnClicked);
    QuitBtn->OnClicked.AddDynamic(this, &UWinUI::QuitBtnClicked);
}

void UWinUI::PlayAgainBtnClicked()
{
    //UGameplayStatics::OpenLevel(GetWorld(),"HideAndSeek_main_menu");
    APlayerControllerBase* PC = Cast<APlayerControllerBase>(GetOwningLocalPlayer()->GetPlayerController(GetWorld()));
    if (PC)
    {
        PC->BackToMainMenu();
    }
}

void UWinUI::QuitBtnClicked()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningLocalPlayer()->GetPlayerController(GetWorld()), EQuitPreference::Quit, true);
}

void UWinUI::SetWiner(EWinner Winner)
{
    switch (Winner)
    {
        case EWinner::Seeker:
           Title->SetText(FText::FromString("Seeker Wins"));
            break;
        case EWinner::Hider:
            Title->SetText(FText::FromString("Hider Wins"));
            break;
    }
}

