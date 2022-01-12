// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowSeekerLoc.h"

void UShowSeekerLoc::CommitAbility()
{
   APawn* Pick = nullptr;
   if(Caster->ActorHasTag("Seeker"))
   {
      TArray<APawn*> Hiders = GetGameState()->Hiders;
      APawn* CloseHider = Hiders[0];
      float ClosestDist = (CloseHider->GetActorLocation() - Caster->GetActorLocation()).Size();
      for(int i = 1; i < Hiders.Num(); i++)
      {
         float Dist = (Hiders[i]->GetActorLocation() - Caster->GetActorLocation()).Size();
         if(ClosestDist > Dist)
         {
            CloseHider = Hiders[i];
            ClosestDist = Dist;
         }
      }
      Pick = CloseHider;
      
      if(Pick)
      {
         ALocationShower* LocationShower = Cast<ALocationShower>(GetWorld()->SpawnActor(SeekerMarkerActor));
         LocationShower->StartShowLocation(Pick, ActiveTime);
      }
   }
   else
   {
      ALocationShower* LocationShower = Cast<ALocationShower>(GetWorld()->SpawnActor(SeekerMarkerActor));
      LocationShower->StartShowLocation(GetGameState()->Seeker, ActiveTime);
   }
   EndAbility();
}
