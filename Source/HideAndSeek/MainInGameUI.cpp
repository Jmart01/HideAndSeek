// Fill out your copyright notice in the Description page of Project Settings.


#include "MainInGameUI.h"
#include "AbilitySwatch.h"
#include "Kismet/GameplayStatics.h"
#include "Ability.h"
#include "PlayerControllerBase.h"

void UMainInGameUI::StartAbilityCoolDown(TSubclassOf<UAbility> AbilityToCoolDown)
{
    for (auto abilityIcon:Swatches)
    {
        if (abilityIcon->AbilityClass == AbilityToCoolDown)
        {
            abilityIcon->StartCoolDown();
        }
    }
}

void UMainInGameUI::OnEscapePressed()
{
    EscapeBtn->SetVisibility(ESlateVisibility::Visible);
    ReturnBtn->SetVisibility(ESlateVisibility::Visible);
}

void UMainInGameUI::NativeConstruct()
{
    EscapeBtn->OnClicked.AddDynamic(this, &UMainInGameUI::EscapeBtnClicked);
    ReturnBtn->OnClicked.AddDynamic(this, &UMainInGameUI::ReturnBtnClicked);
}

void UMainInGameUI::EscapeBtnClicked()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningLocalPlayer()->GetPlayerController(GetWorld()), EQuitPreference::Quit, true);
}

void UMainInGameUI::ReturnBtnClicked()
{
    EscapeBtn->SetVisibility(ESlateVisibility::Hidden);
    ReturnBtn->SetVisibility(ESlateVisibility::Hidden);
    APlayerControllerBase* PC = Cast<APlayerControllerBase>(GetOwningLocalPlayer()->GetPlayerController(GetWorld()));
    if(PC)
    {
        PC->SetModeUIOnly();
    }
}

