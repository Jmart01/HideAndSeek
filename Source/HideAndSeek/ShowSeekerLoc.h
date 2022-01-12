// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "LocationShower.h"
#include "ShowSeekerLoc.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UShowSeekerLoc : public UAbility
{
	GENERATED_BODY()
protected:
	virtual void CommitAbility() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ALocationShower> SeekerMarkerActor;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ActiveTime;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ShowDistance;
};
