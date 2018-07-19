// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameState.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

public:

	AFPSGameMode();

	UFUNCTION()
	void CompleteMission(APawn *InstigatorPawn, bool bMissionSuccess);

	//handled by blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "Gamemode")
	void OnMissionCompleted(APawn *InstigatorPawn, bool bMissionSuccess);
};



