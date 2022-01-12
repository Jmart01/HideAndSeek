// Fill out your copyright notice in the Description page of Project Settings.


#include "TaggingAbility.h"
#include "CharacterBase.h"

void UTaggingAbility::CommitAbility()
{
    TArray<FOverlapResult> OverlapResults;
    Caster->OverLapFront(OverlapResults);
    for(FOverlapResult& overlap: OverlapResults)
    {
        if(overlap.GetActor() && overlap.GetActor() != Caster)
        {
            ACharacterBase* Hider = Cast<ACharacterBase>(overlap.GetActor());
            if (Hider)
            {
                Hider->Caught();
            }
        }
    }
    EndAbility();
}
