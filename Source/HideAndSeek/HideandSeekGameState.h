// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CharacterBase.h"
#include "GameFramework/GameStateBase.h"
#include "HideandSeekGameState.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API AHideandSeekGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="GameState")
	class APawn* Seeker;
	virtual void GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="GameState")
	TArray<class APawn*> Hiders;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category ="GameState")
	int CurrentTime;
};
