// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "JoiningWidget.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UJoiningWidget : public UUserWidget
{
protected:
	GENERATED_BODY()
	void NativeConstruct() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UButton* SeekerBtn;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (BindWidget))
	UButton* HiderBtn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class ACharacterBase> SeekerRoleType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class ACharacterBase> HiderRoleType;
	UPROPERTY()
	bool bSeekerInGame;
	
protected:
	UFUNCTION()
	void SeekerBtnClicked();
	UFUNCTION()
	void HiderBtnClicked();
	
};
