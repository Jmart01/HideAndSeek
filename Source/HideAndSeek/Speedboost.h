// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Speedboost.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API USpeedboost : public UAbility
{
	GENERATED_BODY()
protected:
	virtual void CommitAbility() override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SpeedBoost;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float BoostTime;
	UFUNCTION()
	void BoostEnded();
};
