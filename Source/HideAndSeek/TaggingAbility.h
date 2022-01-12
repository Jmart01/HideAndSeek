// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "TaggingAbility.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UTaggingAbility : public UAbility
{
	GENERATED_BODY()
protected:
    virtual void CommitAbility() override;
};
