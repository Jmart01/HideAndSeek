// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharacterBase.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovedDelegate);
UCLASS()
class HIDEANDSEEK_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
	/****************************************************
	*					Initialization					*
	****************************************************/
public:
	// Sets default values for this character's properties
	ACharacterBase();
	virtual void PossessedBy(AController* NewController) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UMainInGameUI> InGameUIClass;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TSubclassOf<class UserWidget> WinUIClass;
	UFUNCTION(Client, Reliable)
	void SpawnInGameUI();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/****************************************************
	*					Components						*
	****************************************************/
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	USpringArmComponent* PlayerEyeSpringArm;
	UCameraComponent* PlayerEye;



	
	/****************************************************
	*					Inputs							*
	****************************************************/
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveForward(float amount);
	void MoveRight(float amount);
	void Turn(float amount);
	void LookUp(float amount);
	void Escape();
	void KeyPressed(FKey InputKey);

	/****************************************************
	*					Abilities						*
	****************************************************/
public:
	UFUNCTION(Server, Reliable, WithValidation)
	void Caught();
	UFUNCTION(Client, Reliable)
	void DestroyUI();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TMap<FKey, TSubclassOf<class UAbility>> Abilities;
	void StartAbilityCoolDown(float CoolDownTime, FName CoolDownTag);
	void AbilityCooledDown(FName CoolDownTag);
	void OnAbilityEnded(class UAbility* AbilityEnded);

	void OverLapFront(TArray<FOverlapResult>& OutOverlapResults);
	FOnMovedDelegate OnMoved;
	FOnMovedDelegate OnStopedMoving;
	void BroadCastMovement();
protected:
	UFUNCTION()
	class AHideAndSeekGameModeBase* GetGameMode();
	UFUNCTION(Server,Reliable,WithValidation)
	void Server_CastAbility(TSubclassOf<class UAbility> AbilityToCast);
	TArray<class UAbility*> CurrentActiveAbilities;
	/****************************************************
	*					UI								*
	****************************************************/
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ReturnCooldownAndPercentValues(float percentValue, TSubclassOf<class UAbility> AbilityToCoolDown);
	FTimerHandle LocalUIAbilityCoolDownHandle;
	FTimerHandle LocalUIAbilityCoolDownTickHandle;
protected:
	UFUNCTION(Client, reliable)
	void C_StartUICoolDown(float coolDownTime, TSubclassOf<class UAbility> AbilityToCoolDown);

private:
	class UMainInGameUI* InGameUI;
	class UWinUI* WinUI;
	float PreviousSpeed;
	
};






