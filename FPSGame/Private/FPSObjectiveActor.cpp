// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"


// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Cast<USceneComponent>(MeshComp);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp")); 
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(Cast<USceneComponent>(MeshComp));

	SetReplicates(true);

}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
	
}

//method that notify when overlap with objective
void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	if (Role == ROLE_Authority)
	{
		AFPSCharacter *MyCharacter = Cast<AFPSCharacter>(OtherActor);
		if (MyCharacter)
		{
			MyCharacter->bIsCarryingObjective = true;
			Destroy();
		}
	}
}

void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

