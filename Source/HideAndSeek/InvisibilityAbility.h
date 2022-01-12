// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "InvisibilityAbility.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UInvisibilityAbility : public UAbility
{
	GENERATED_BODY()


protected:
    virtual void CommitAbility() override;

public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite)
    float InvisibilityTime;
    UFUNCTION()
    void VisibleAgain();
};
