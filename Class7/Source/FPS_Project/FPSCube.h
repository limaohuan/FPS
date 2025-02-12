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

	// ����ķ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cube Properties")
	int Point;

	// ����Ĳ���
	UPROPERTY(EditAnywhere, Category = "Cube Properties")
	UMaterialInterface* CubeMaterial;

	// ���� 5 �ֵĲ���
	UPROPERTY(EditAnywhere, Category = "Cube Properties")
	UMaterialInterface* FivePointMaterial;

	// ���� 10 �ֵĲ���
	UPROPERTY(EditAnywhere, Category = "Cube Properties")
	UMaterialInterface* TenPointMaterial;

	// ���ѡ�������5 �� 10��
	int GetRandomPoint();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ���з���ʱ���õĺ���
	void HitBox(AFPS_ProjectCharacter* FPSCharacter);

	// ���÷���ķ���
	void SetPoint(int NewPoint);

	// ���÷���Ĳ���
	UFUNCTION(BlueprintCallable, Category = "Cube Properties")
	void SetCubeMaterial(UMaterialInterface* NewMaterial);

	// ��ȡ�������
	int GetCubePoint();

	// ���÷�������
	void SetCube();
};
