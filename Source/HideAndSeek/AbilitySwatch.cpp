// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySwatch.h"
#include "Ability.h"
#include "Components/Image.h"
void UAbilitySwatch::StartCoolDown()
{
    UAbility* DOJ = AbilityClass.GetDefaultObject();
    coolDownTime = DOJ->GetCoolDownTime();
    GetWorld()->GetTimerManager().SetTimer(CoolDownFullTimeHandle, coolDownTime,false);
    GetWorld()->GetTimerManager().SetTimer(CoolDownTickHandle, this, &UAbilitySwatch::CoolDownTick,0.1,true);
}

void UAbilitySwatch::CoolDownTick()
{
    float TimeElapes = GetWorld()->GetTimerManager().GetTimerElapsed(CoolDownFullTimeHandle);
    float Percentage = TimeElapes/coolDownTime;
    if (TimeElapes == -1)
    {
        Percentage = 1;
        GetWorld()->GetTimerManager().ClearTimer(CoolDownTickHandle);
    }
    //UE_LOG(LogTemp, Warning, TEXT("percentage: %f"), Percentage);
    Ability_Icon->GetDynamicMaterial()->SetScalarParameterValue("percent", Percentage);
}
