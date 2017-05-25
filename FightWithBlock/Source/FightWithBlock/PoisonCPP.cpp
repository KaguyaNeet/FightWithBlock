// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "PoisonCPP.h"


// Sets default values
APoisonCPP::APoisonCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoisonCPP::BeginPlay()
{
	Super::BeginPlay();

	BlueprintDelayDestroy();
	
}

// Called every frame
void APoisonCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

