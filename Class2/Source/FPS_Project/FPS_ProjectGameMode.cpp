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

	// ����ÿ֡ Tick
	PrimaryActorTick.bCanEverTick = true;

}

void AFPS_ProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	// ������ʱ����ÿ�����һ�� UpdateTimer ����
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFPS_ProjectGameMode::UpdateTimer, 1.0f, true);

	// ������Ϸ����ʱ
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFPS_ProjectGameMode::EndGame, GameTimeLimit, false);

}

void AFPS_ProjectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPS_ProjectGameMode::EndGame()
{
	FString FinalScore;

	// ��ȡFPSCharacter
	AFPS_ProjectCharacter* FPSCharacter = Cast<AFPS_ProjectCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (FPSCharacter)
	{
		FinalScore = FString::Printf(TEXT("FinalScore: %.2f"), FPSCharacter->GetScore());
	}

	// ��ʾ������Ϣ���롣 
	// �����е�-1"��"ֵ���Ͳ����ܷ�ֹ����Ϣ�����»�ˢ�¡�
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Game Over!"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FinalScore);
}

void AFPS_ProjectGameMode::UpdateTimer()
{
	if (GameTimeLimit > 0)
	{
		GameTimeLimit -= 1;
	}
	else
	{
		// ʱ�����ֹ꣬ͣ��ʱ��
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}
