// Fill out your copyright notice in the Description page of Project Settings.


#include "Speedboost.h"
#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
void USpeedboost::CommitAbility()
{
    Caster->GetCharacterMovement()->MaxWalkSpeed*=SpeedBoost;
    FTimerHandle TH;
    GetWorld()->GetTimerManager().SetTimer(TH, this, &USpeedboost::BoostEnded, BoostTime);
}

void USpeedboost::BoostEnded()
{
    Caster->GetCharacterMovement()->MaxWalkSpeed/=SpeedBoost;
    EndAbility();
}
