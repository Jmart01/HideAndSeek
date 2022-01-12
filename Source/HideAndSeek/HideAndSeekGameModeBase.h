// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerBase.h"
#include "GameFramework/GameModeBase.h"
#include "HideAndSeekGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API AHideAndSeekGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	public:
	AHideAndSeekGameModeBase();
	virtual void BeginPlay() override;
	FTimerHandle TimeCounter;
	FTimerHandle FullTimeHanle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Gameplay")
	int GameTimeMinutes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="GamePlay")
	TSubclassOf<UWinUI> WinUIClass;
	UFUNCTION()
	void StartGameCounting();
	UFUNCTION()
	void TimerCountFunc();
	UFUNCTION()
	void TimeEnded();
	void HiderCaught(APawn* Hider);
	void GameFinished(EWinner Winner);
	void BackToMainMenu();
};
