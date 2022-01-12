// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ObjectMacros.h"

#include "AbilitySwatch.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UAbilitySwatch : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	class UImage* Ability_Icon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Icon")
	TSubclassOf<class UAbility> AbilityClass;
	void StartCoolDown();
	FTimerHandle CoolDownTickHandle;
	FTimerHandle CoolDownFullTimeHandle;

	UFUNCTION()
	void CoolDownTick();
private:
	float coolDownTime;
};
