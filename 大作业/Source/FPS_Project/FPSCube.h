// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSCube.generated.h"

class AFPS_ProjectCharacter;

UCLASS()
class FPS_PROJECT_API AFPSCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;

	bool Hitted = false;

	// 方块的分数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cube Properties")
	int Point;

	// 方块的材质
	UPROPERTY(EditAnywhere, Category = "Cube Properties")
	UMaterialInterface* CubeMaterial;

	// 方块 5 分的材质
	UPROPERTY(EditAnywhere, Category = "Cube Properties")
	UMaterialInterface* FivePointMaterial;

	// 方块 10 分的材质
	UPROPERTY(EditAnywhere, Category = "Cube Properties")
	UMaterialInterface* TenPointMaterial;

	// 随机选择分数（5 或 10）
	int GetRandomPoint();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 命中方块时调用的函数
	void HitBox(AFPS_ProjectCharacter* FPSCharacter);

	// 设置方块的分数
	void SetPoint(int NewPoint);

	// 设置方块的材质
	UFUNCTION(BlueprintCallable, Category = "Cube Properties")
	void SetCubeMaterial(UMaterialInterface* NewMaterial);

	// 获取方块分数
	int GetCubePoint();

	// 设置方块属性
	void SetCube();
};
