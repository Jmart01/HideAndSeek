// Fill out your copyright notice in the Description page of Project Settings.


#include "HideandSeekGameState.h"

#include "Net/UnrealNetwork.h"

void AHideandSeekGameState::GetLifetimeReplicatedProps(::TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AHideandSeekGameState, Seeker);
    DOREPLIFETIME(AHideandSeekGameState, Hiders);
    DOREPLIFETIME(AHideandSeekGameState, CurrentTime);
}
