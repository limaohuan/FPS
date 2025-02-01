// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPS_ProjectGameMode.generated.h"

UCLASS(minimalapi)
class AFPS_ProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPS_ProjectGameMode();


protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    // ��Ϸʱ�����ƣ���λ���룩
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Timer")
    float GameTimeLimit = 20.0f;

    // ��Ϸ����ʱ���õĺ���
    UFUNCTION(BlueprintImplementableEvent, Category = "GameOver")
    void EndGame();

    
};



