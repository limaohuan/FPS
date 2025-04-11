// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_ProjectGameMode.h"
#include "FPS_ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/TextBlock.h"

AFPS_ProjectGameMode::AFPS_ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// ÆôÓÃÃ¿Ö¡ Tick
	PrimaryActorTick.bCanEverTick = true;

}

void AFPS_ProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void AFPS_ProjectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameTimeLimit > 0)
	{
		GameTimeLimit -= DeltaTime;
		if (GameTimeLimit <= 0)
		{
			EndGame();
		}
	}
}



