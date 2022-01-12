// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"

#include "NoiseGeneratorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HIDEANDSEEK_API UNoiseGeneratorComponent : public UAudioComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNoiseGeneratorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void StartMakingNoiseTimer();
	UFUNCTION(NetMulticast, Reliable)
	void MakeNoise();
	
	UFUNCTION(NetMulticast, Reliable)
	void StopNoise();
	FTimerHandle StayingTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Noise Maker")
	float StayMaximumTime;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
