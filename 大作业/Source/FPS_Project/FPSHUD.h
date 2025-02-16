// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPSHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPS_PROJECT_API AFPSHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPSHUD();

protected:
	virtual void DrawHUD() override;
	
	
	
};
