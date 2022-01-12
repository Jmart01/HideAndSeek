// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PlayerControllerBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "WinUI.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UWinUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UButton* PlayAgainBtn;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UButton* QuitBtn;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UTextBlock* Title;
	
	UFUNCTION()
	void PlayAgainBtnClicked();
	UFUNCTION()
	void QuitBtnClicked();
	public:
	void SetWiner(EWinner Winner);
};
