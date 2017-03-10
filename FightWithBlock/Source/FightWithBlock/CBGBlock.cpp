// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "CBGBlock.h"


// Sets default values
ACBGBlock::ACBGBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetWorldScale3D(FVector(3.f, 3.f, 3.f));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	//测试用！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	ConstructorHelpers::FObjectFinder<UStaticMesh> textMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (textMesh.Succeeded())
		CollisionComponent->SetStaticMesh(textMesh.Object);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetMobility(EComponentMobility::Movable);
	StaticMesh->AttachTo(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//测试用的添加了StaticMesh！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	if (CubeMesh.Succeeded())
		StaticMesh->SetStaticMesh(CubeMesh.Object);
	StaticMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
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