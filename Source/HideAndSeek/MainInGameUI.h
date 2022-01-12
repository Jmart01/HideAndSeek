// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainInGameUI.generated.h"


/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UMainInGameUI : public UUserWidget
{
	GENERATED_BODY()
public:
    void StartAbilityCoolDown(TSubclassOf<class UAbility> AbilityToCoolDown);
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Icon")
    TArray<class UAbilitySwatch*> Swatches;
    UFUNCTION(BlueprintImplementableEvent)
    void Init(class ACharacterBase* OnwerPawn);
    UFUNCTION()
    void OnEscapePressed();
    void NativeConstruct() override;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
    UButton* EscapeBtn;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
    UButton* ReturnBtn;
protected:
    UFUNCTION()
    void EscapeBtnClicked();
    UFUNCTION()
    void ReturnBtnClicked();
};
