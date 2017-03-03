// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "BoltBlock.h"


// Sets default values
ABoltBlock::ABoltBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetMobility(EComponentMobility::Movable);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

// Called when the game starts or when spawned
void ABoltBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoltBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

