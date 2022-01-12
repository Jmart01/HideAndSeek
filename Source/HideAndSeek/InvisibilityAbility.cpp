// Fill out your copyright notice in the Description page of Project Settings.


#include "InvisibilityAbility.h"
#include "CharacterBase.h"

void UInvisibilityAbility::CommitAbility()
{
    Caster->SetActorHiddenInGame(true);
    FTimerHandle Inv;
    GetWorld()->GetTimerManager().SetTimer(Inv,this, &UInvisibilityAbility::VisibleAgain,InvisibilityTime);
}

void UInvisibilityAbility::VisibleAgain()
{
    Caster->SetActorHiddenInGame(false);
    EndAbility();
}
