// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EWinner : uint8
{
	Seeker,
	Hider
};

UCLASS()
class HIDEANDSEEK_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(Client, Reliable)	
	void GameFinished(EWinner Winner, TSubclassOf<class UWinUI> UI);
	UFUNCTION(Server, Reliable, WithValidation)
	void BackToMainMenu();
	class UWinUI* WinUI;	
	void SetModeUIOnly();

	void SetModeGameOnly();
};
