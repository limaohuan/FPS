// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCube.h"
#include "FPS_ProjectCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSCube::AFPSCube()
{
    // ����Actor����Ϊÿ֡����Tick()��  �������Ҫ�����ԣ����Թر����������ܡ�
    PrimaryActorTick.bCanEverTick = true;

    //�������ǵ�Ĭ�����
    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

    //���������������Ч��
    BoxComp->SetupAttachment(RootComponent);
    BoxComp->SetSimulatePhysics(true);
    BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    StaticMeshComp->AttachToComponent(BoxComp, FAttachmentTransformRules::KeepRelativeTransform);

    //ͨ�����츨������������̬������������óɷ�����״��
    static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
    StaticMeshComp->SetStaticMesh(CubeMeshAsset.Object);

    // Ĭ�Ϸ���Ϊ0
    Point = 0;

    FivePointMaterial = nullptr;  // Ĭ�ϲ���Ϊ��
    TenPointMaterial = nullptr;  // Ĭ�ϲ���Ϊ��

}

// Called when the game starts or when spawned
void AFPSCube::BeginPlay()
{
	Super::BeginPlay();

    // ������÷���Ĳ��ʺͷ���
    SetCube();
}

int AFPSCube::GetCubePoint()
{
    return Point;
}

void AFPSCube::SetCube()
{
    int CubePoint = GetRandomPoint();
    SetPoint(CubePoint);
    // ���ݷ������ò���
    if (CubePoint == 5 && FivePointMaterial)
    {
        SetCubeMaterial(FivePointMaterial);
    }
    else if (CubePoint == 10 && TenPointMaterial)
    {
        SetCubeMaterial(TenPointMaterial);
    }
}

int AFPSCube::GetRandomPoint()
{
    // 20% �ļ��ʸ� 10 �֣�80% �ļ��ʸ� 5 ��
    return FMath::RandRange(0, 99) < 20 ? 10 : 5;
}

// Called every frame
void AFPSCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSCube::HitBox(AFPS_ProjectCharacter* FPSCharacter)
{
    if (!Hitted)
    {
        StaticMeshComp->SetRelativeScale3D(FVector(0.5, 0.5, 0.5));
        Hitted = true;
    }
    else
    {
        FPSCharacter->AddScore(Point);
        Destroy();
    }
}

void AFPSCube::SetPoint(int NewPoint)
{
    Point = NewPoint;
}

void AFPSCube::SetCubeMaterial(UMaterialInterface* NewMaterial)
{
    if (NewMaterial)
    {
        StaticMeshComp->SetMaterial(0, NewMaterial);
    }
}
