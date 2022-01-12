// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HideandSeekGameState.h"

#include "Ability.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class HIDEANDSEEK_API UAbility : public UObject
{
	GENERATED_BODY()
public:
    void TryActivateAbility(class ACharacterBase* AbilityCaster);
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    FName AbilityCoolDownTag;
    float GetCoolDownTime() const {return CoolDownTime;}
protected:
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float CoolDownTime;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PreCastTime;
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    class UTexture2D* AbilityIcon;

    FTimerHandle CasterTimerHandle;
    virtual void CommitAbility();
    virtual bool bCanCastAbility();
    class ACharacterBase* Caster;
    virtual void EndAbility();
    AHideandSeekGameState* GetGameState();
};
