// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "CBGBlock.h"


// Sets default values
ACBGBlock::ACBGBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->OnComponentHit.__Internal_AddDynamic(this, &ACBGBlock::OnHit, TEXT("OnHit"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetMobility(EComponentMobility::Movable);
	StaticMesh->AttachTo(RootComponent);
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

void ACBGBlock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, FVector NormalImpulse, const FHitResult& Hit)
{

}

void ACBGBlock::DestroySelf()
{
	this->Destroy(true);
}