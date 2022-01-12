// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "CharacterBase.h"
#include "DefaultSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API ADefaultSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	UFUNCTION(Server, Reliable, WithValidation)
	void StartsPlay(TSubclassOf<class ACharacterBase> PawnType, bool isSeeker=false);
	UUserWidget* JoiningWidget;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class UUserWidget> JoingWidgetType;
	
};
