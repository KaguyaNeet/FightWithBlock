// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "CBGBlock.h"
#include "NET/UnrealNetwork.h"

// Sets default values
ACBGBlock::ACBGBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetMobility(EComponentMobility::Movable);
	CollisionComponent->SetSphereRadius(30.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetEnableGravity(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetMobility(EComponentMobility::Movable);
	StaticMesh->AttachTo(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	//测试用的添加了StaticMesh！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	//ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	//if (CubeMesh.Succeeded())
	//	StaticMesh->SetStaticMesh(CubeMesh.Object);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (CollisionComponent->GetBodyInstance())
	{
		CollisionComponent->GetBodyInstance()->bLockXRotation = true;
		CollisionComponent->GetBodyInstance()->bLockXRotation = true;
		CollisionComponent->GetBodyInstance()->bLockXTranslation = true;
		CollisionComponent->GetBodyInstance()->bLockYTranslation = true;
	}

	


}

// Called when the game starts or when spawned
void ACBGBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBGBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Spin(DeltaTime);

}

void ACBGBlock::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACBGBlock, BlockProperty);
	DOREPLIFETIME(ACBGBlock, IsInit);
	
}

void ACBGBlock::floatUpDown()
{

}

void ACBGBlock::SetInitProperty(FBlock Block)
{
	IsInit = true;
	BlockProperty = Block;
	StaticMesh->SetStaticMesh(BlockProperty.StaticMesh);
	StaticMesh->SetMaterial(0, BlockProperty.Material);
	UGameplayStatics::SpawnEmitterAttached(BlockProperty.selfParticle, StaticMesh);
	StaticMesh->SetWorldScale3D(StaticMesh->GetComponentScale() * BlockProperty.Size);
}
void ACBGBlock::OnRep_Init()
{
	SetInitProperty(BlockProperty);
}

void ACBGBlock::DestroySelf()
{
	this->Destroy(true);
}

void ACBGBlock::Spin(float DeltaTime)
{
	SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + DeltaTime * SpinSpeed, GetActorRotation().Roll));
}
