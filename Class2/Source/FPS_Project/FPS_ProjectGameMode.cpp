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

	// 启用每帧 Tick
	PrimaryActorTick.bCanEverTick = true;

}

void AFPS_ProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	// 启动计时器，每秒调用一次 UpdateTimer 函数
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFPS_ProjectGameMode::UpdateTimer, 1.0f, true);

	// 启动游戏倒计时
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AFPS_ProjectGameMode::EndGame, GameTimeLimit, false);

}

void AFPS_ProjectGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPS_ProjectGameMode::EndGame()
{
	FString FinalScore;

	// 获取FPSCharacter
	AFPS_ProjectCharacter* FPSCharacter = Cast<AFPS_ProjectCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (FPSCharacter)
	{
		FinalScore = FString::Printf(TEXT("FinalScore: %.2f"), FPSCharacter->GetScore());
	}

	// 显示调试消息五秒。 
	// 参数中的-1"键"值类型参数能防止该消息被更新或刷新。
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
		// 时间用完，停止计时器
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}
}
