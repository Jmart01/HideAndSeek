// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"
#include "CharacterBase.h"

void UAbility::TryActivateAbility(class ACharacterBase* AbilityCaster)
{
    Caster = AbilityCaster;
    //Debug line here to make sure the ability is getting here
    if(bCanCastAbility())
    {
        Caster->StartAbilityCoolDown(CoolDownTime,AbilityCoolDownTag);
        //Caster->PlayAnimation(AbilityMontage);
        GetWorld()->GetTimerManager().SetTimer(CasterTimerHandle,this,&UAbility::CommitAbility,PreCastTime);
    }
}

void UAbility::CommitAbility()
{
    EndAbility();
}

bool UAbility::bCanCastAbility()
{
    if(Caster && Caster->ActorHasTag(AbilityCoolDownTag))
    {
        return false;
    }
    return true;
}

void UAbility::EndAbility()
{
    Caster->OnAbilityEnded(this);
}

AHideandSeekGameState* UAbility::GetGameState()
{
    AHideandSeekGameState* GameState = Cast<AHideandSeekGameState>(GetWorld()->GetGameState());
    return GameState;
}
