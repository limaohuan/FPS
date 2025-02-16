// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCube.h"
#include "FPS_ProjectCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSCube::AFPSCube()
{
    // 将此Actor设置为每帧调用Tick()。  如果不需要此特性，可以关闭以提升性能。
    PrimaryActorTick.bCanEverTick = true;

    //创建我们的默认组件
    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

    //绑定组件并设置物理效果
    BoxComp->SetupAttachment(RootComponent);
    BoxComp->SetSimulatePhysics(true);
    BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    StaticMeshComp->AttachToComponent(BoxComp, FAttachmentTransformRules::KeepRelativeTransform);

    //通过构造辅助函数，将静态网格体组件设置成方块形状。
    static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
    StaticMeshComp->SetStaticMesh(CubeMeshAsset.Object);

    // 默认分数为0
    Point = 0;

    FivePointMaterial = nullptr;  // 默认材质为空
    TenPointMaterial = nullptr;  // 默认材质为空

}

// Called when the game starts or when spawned
void AFPSCube::BeginPlay()
{
	Super::BeginPlay();

    // 随机设置方块的材质和分数
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
    // 根据分数设置材质
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
    // 20% 的几率给 10 分，80% 的几率给 5 分
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
