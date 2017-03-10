// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "CBGBlock.h"


// Sets default values
ACBGBlock::ACBGBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetMobility(EComponentMobility::Movable);
	CollisionComponent->SetSphereRadius(100.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetEnableGravity(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetMobility(EComponentMobility::Movable);
	StaticMesh->AttachTo(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//测试用的添加了StaticMesh！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	if (CubeMesh.Succeeded())
		StaticMesh->SetStaticMesh(CubeMesh.Object);
	StaticMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	if (StaticMesh->GetBodyInstance())
	{
		StaticMesh->GetBodyInstance()->bLockXRotation = true;
		StaticMesh->GetBodyInstance()->bLockXRotation = true;
		StaticMesh->GetBodyInstance()->bLockXTranslation = true;
		StaticMesh->GetBodyInstance()->bLockYTranslation = true;
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

void ACBGBlock::floatUpDown()
{

}

void ACBGBlock::SetInitProperty(FBlock Block)
{
	BlockProperty = Block;
}

void ACBGBlock::DestroySelf()
{
	this->Destroy(true);
}

void ACBGBlock::Spin(float DeltaTime)
{
	SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + DeltaTime * SpinSpeed, GetActorRotation().Roll));
}

void ACBGBlock::Drop(FVector Direction)
{
	CollisionComponent->AddForce(Direction * DropForce);
}