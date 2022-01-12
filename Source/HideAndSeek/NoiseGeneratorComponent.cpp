// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseGeneratorComponent.h"
#include "CharacterBase.h"
// Sets default values for this component's properties
UNoiseGeneratorComponent::UNoiseGeneratorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	StayMaximumTime = 3.f;
	VolumeMultiplier = 0.f;
	// ...
}


// Called when the game starts
void UNoiseGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();
	ACharacterBase* OwnerCharacterBase = Cast<ACharacterBase>(GetOwner());
	if (OwnerCharacterBase)
	{
		OwnerCharacterBase->OnMoved.AddDynamic(this,&UNoiseGeneratorComponent::StopNoise);
		OwnerCharacterBase->OnStopedMoving.AddDynamic(this,&UNoiseGeneratorComponent::StartMakingNoiseTimer);
		StartMakingNoiseTimer();
	}
}

void UNoiseGeneratorComponent::StartMakingNoiseTimer()
{
	GetWorld()->GetTimerManager().SetTimer(StayingTimer,this, &UNoiseGeneratorComponent::MakeNoise,StayMaximumTime);
}

void UNoiseGeneratorComponent::MakeNoise_Implementation()
{
	SetVolumeMultiplier(1.0f);
}

void UNoiseGeneratorComponent::StopNoise_Implementation()
{
	SetVolumeMultiplier(0.0f);
	GetWorld()->GetTimerManager().ClearTimer(StayingTimer);
}

// Called every frame
void UNoiseGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

