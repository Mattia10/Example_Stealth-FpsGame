// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"

AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp")); 

	GuardState = EAIState::Idle;
}

void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();
	
}

void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//to bind PawnSensing method
void AFPSAIGuard::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
		return;
	
	GuardState = NewState;	
	OnRep_GuardState();
}

void AFPSAIGuard::OnRep_GuardState()
{
	OnStateChanged(GuardState);
}

//logic: when guards hear a noise, they turn in the direction of the noise
//		 past 3 seconds, turn again in the original position
void AFPSAIGuard::OnNoiseHeard(APawn * NoiseInstigator, const FVector & Location, float Volume)
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);


	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);

	SetGuardState(EAIState::Suspicious);
}

//logic: when guards see player, call "CompleteMission" method and game over
//		 "DrawDebugSphere" just for test
void AFPSAIGuard::OnPawnSeen(APawn * SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	AFPSGameMode *GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
		GM->CompleteMission(SeenPawn, false);

	UE_LOG(LogTemp, Warning, TEXT("SeenPawn!"));
	//DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false,  10.0f);	

	SetGuardState(EAIState::Alerted);
}

// method to reset orientation when guards turns into idle state
void AFPSAIGuard::ResetOrientation()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::Idle);

}

// method to replicate variable
void AFPSAIGuard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSAIGuard, GuardState);
}