// Fill out your copyright notice in the Description page of Project Settings.


#include "LocationShower.h"

// Sets default values
ALocationShower::ALocationShower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ALocationShower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocationShower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALocationShower::StartShowLocation(AActor* ActorToShow, float ShowTime)
{
	AttachToActor(ActorToShow,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer,this,&ALocationShower::DestroySelf,ShowTime,false);
}

void ALocationShower::DestroySelf()
{
	Destroy();
}

