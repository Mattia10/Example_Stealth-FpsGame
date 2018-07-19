// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "FPSObjectiveActor.generated.h"



UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent *SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem *PickupFX; 

	void PlayEffects();

public:	
	void BeginPlay()override;

	virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;
	
	
};
