// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ability.h"
#include "DrawDebugHelpers.h"
#include "HideAndSeekGameModeBase.h"
#include "MainInGameUI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpectatorPawn.h"
#include "GameFramework/PlayerController.h"
// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerEyeSpringArm = CreateDefaultSubobject<USpringArmComponent>("PlayerEyeSpringArm");
	PlayerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	PlayerEyeSpringArm->SetupAttachment(GetRootComponent());
	PlayerEye->SetupAttachment(PlayerEyeSpringArm, USpringArmComponent::SocketName);
	PlayerEyeSpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,600, 0);
	SetReplicates(true);
}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	SpawnInGameUI();
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::SpawnInGameUI_Implementation()
{
	if(GetLocalRole() == ROLE_AutonomousProxy || (IsLocallyControlled() && HasAuthority()))
	{
		if(GetController() && GetController()->IsPlayerController())
		{
			UWidgetComponent* WidgetComponent = Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()));
			if(WidgetComponent)
			{
				WidgetComponent->SetVisibility(false);
			}
			if(InGameUIClass)
			{
				InGameUI = Cast<UMainInGameUI>(CreateWidget(Cast<APlayerController>(GetController()),InGameUIClass));
				if(InGameUI)
				{
					InGameUI->Init(this);
					InGameUI->AddToViewport();
				}

			}
		}
	}
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
	}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(HasAuthority())
	{
		BroadCastMovement();		
	}
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ensure(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterBase::Jump);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacterBase::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterBase::LookUp);
	PlayerInputComponent->BindAction("Escape", IE_Pressed, this, &ACharacterBase::Escape);

	FInputChord KeyChord(EKeys::AnyKey);
	FInputKeyBinding KB(KeyChord, IE_Pressed);
	KB.KeyDelegate.BindDelegate(this, &ACharacterBase::KeyPressed);
	PlayerInputComponent->KeyBindings.Emplace(MoveTemp(KB));
}
/****************************************************
*					Movements						*
****************************************************/
void ACharacterBase::BroadCastMovement()
{
	if(HasAuthority())
	{
		float CurrentSpeed = GetCharacterMovement()->GetLastUpdateVelocity().Size();
		if(PreviousSpeed == 0 && CurrentSpeed != 0)
		{
			OnMoved.Broadcast();
		}
		if (PreviousSpeed != 0 && CurrentSpeed == 0)
		{
			OnStopedMoving.Broadcast();
		}
		PreviousSpeed = CurrentSpeed;
	}
}

AHideAndSeekGameModeBase* ACharacterBase::GetGameMode()
{
	if (HasAuthority())
	{
		return Cast<AHideAndSeekGameModeBase>(GetWorld()->GetAuthGameMode());
	}
	return nullptr;
}

void ACharacterBase::DestroyUI_Implementation()
{
	if(InGameUI)
	{
		InGameUI->RemoveFromParent();
	}
}

void ACharacterBase::MoveForward(float amount)
{
	if(amount!=0)
	{
		FVector ViewLoc;
		FRotator ViewRot;
		GetController()->GetPlayerViewPoint(ViewLoc, ViewRot);
		FVector ForwardDir = ViewRot.Vector();
		AddMovementInput(ForwardDir, amount);
	}
}

void ACharacterBase::MoveRight(float amount)
{
	if(amount!=0)
	{
		FVector RightDir = PlayerEye->GetRightVector();
		AddMovementInput(RightDir,amount);
	}
}

void ACharacterBase::Turn(float amount)
{
	AddControllerYawInput(amount);
}

void ACharacterBase::LookUp(float amount)
{
	AddControllerPitchInput(amount);
}

void ACharacterBase::Escape()
{
	if(InGameUI)
	{
		APlayerControllerBase* PC = Cast<APlayerControllerBase>(GetController());
		if (PC)
		{
			InGameUI->OnEscapePressed();
			PC->SetModeUIOnly();
		}
	}
}

/****************************************************
*					abilities						*
****************************************************/

void ACharacterBase::StartAbilityCoolDown(float CoolDownTime, FName CoolDownTag)
{
	Tags.AddUnique(CoolDownTag);
	FTimerHandle CoolDownTimerHandle;
	FTimerDelegate CoolDownDelegate = FTimerDelegate::CreateUObject(this, &ACharacterBase::AbilityCooledDown, CoolDownTag);
	GetWorldTimerManager().SetTimer(CoolDownTimerHandle, CoolDownDelegate, CoolDownTime, false);

	for(auto ability: Abilities)
	{
		if(ability.Value.GetDefaultObject()->AbilityCoolDownTag == CoolDownTag)
		{
			C_StartUICoolDown(CoolDownTime, ability.Value);
		}
	}
}

void ACharacterBase::AbilityCooledDown(FName CoolDownTag)
{
	Tags.Remove(CoolDownTag);
}

void ACharacterBase::OnAbilityEnded(UAbility* AbilityEnded)
{
	CurrentActiveAbilities.Remove(AbilityEnded);
}

void ACharacterBase::OverLapFront(TArray<FOverlapResult>& OutOverlapResults)
{
	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_Pawn);
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(100.f);
	GetWorld()->OverlapMultiByObjectType(
		OutOverlapResults,
		GetActorLocation() + GetActorForwardVector() * 80,
		FQuat(),
		QueryParams,
		CollisionShape);
	DrawDebugSphere(GetWorld(), GetActorLocation() +GetActorForwardVector() *80, 100.f, 12, FColor::Red, false, 2);
}

void ACharacterBase::Server_CastAbility_Implementation(TSubclassOf<UAbility> AbilityToCast)
{
	UAbility* newAbility = NewObject<UAbility>(this, AbilityToCast);
	CurrentActiveAbilities.Add(newAbility);
	newAbility->TryActivateAbility(this);
}

bool ACharacterBase::Server_CastAbility_Validate(TSubclassOf<UAbility> AbilityToCast)
{
	return true;
}

/****************************************************
*					UI								*
****************************************************/

void ACharacterBase::C_StartUICoolDown_Implementation(float cooldownTime, TSubclassOf<UAbility> AbilityToCoolDown)
{
	if(InGameUI)
	{
		InGameUI->StartAbilityCoolDown(AbilityToCoolDown);
	}
}

/****************************************************
*					Inputs							*
****************************************************/

void ACharacterBase::KeyPressed(FKey InputKey)
{
	for(auto Ability:Abilities)
	{
		FKey HotKey = Ability.Key;
		if(HotKey == InputKey)
		{
			UE_LOG(LogTemp,Warning,TEXT("Ive been pressed, and i am"));
			Server_CastAbility(Ability.Value);
		}
	}
}

void ACharacterBase::Caught_Implementation()
{
	DestroyUI();
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		APawn* SpectatorPawn = Cast<ASpectatorPawn>(GetWorld()->SpawnActor(ASpectatorPawn::StaticClass(),&GetActorTransform()));
		if(SpectatorPawn)
		{
			PC->Possess(SpectatorPawn);
			auto GM = GetGameMode();
			if (GM)
			{
				GM->HiderCaught(this);
			}
			Destroy();
		}
	}
	
}

bool ACharacterBase::Caught_Validate()
{
	return true;
}
