// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "Net/UnrealNetwork.h"
#include "FPSAIGuard.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};

class UPawnSensingComponent;
UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	void SetGuardState(EAIState NewState);
	
	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;

	UFUNCTION()
	void OnRep_GuardState();

	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent *PawnSensingComp;

	UFUNCTION()
	void ResetOrientation();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
	void OnPawnSeen(APawn *SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn *NoiseInstigator, const FVector &Location, float Volume);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState NewState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
