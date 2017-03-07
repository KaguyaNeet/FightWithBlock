// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "BlockBase.h"


// Sets default values
ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachTo(RootComponent);
	StaticMesh->SetLockedAxis(EDOFMode::Default);
	StaticMesh->SetConstraintMode(EDOFMode::Default);
	if (StaticMesh->GetBodyInstance())
	{
		StaticMesh->GetBodyInstance()->bLockXTranslation = true;
		StaticMesh->GetBodyInstance()->bLockYTranslation = true;
		StaticMesh->GetBodyInstance()->bLockXRotation = true;
		StaticMesh->GetBodyInstance()->bLockYRotation = true;
		StaticMesh->GetBodyInstance()->bLockZRotation = true;
	}
	StaticMesh->SetMobility(EComponentMobility::Static);

}

// Called when the game starts or when spawned
void ABlockBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockBase::SetInitProperty(FBlock Block)
{
	BlockProperty = Block;
}

void ABlockBase::BeBreak()
{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParameter;
			SpawnParameter.Owner = this;
			SpawnParameter.Instigator = Instigator;
			if (BlockProperty.breakParticle && BlockProperty.breakParticle->IsTemplate())
				UGameplayStatics::SpawnEmitterAtLocation(World, BlockProperty.breakParticle, GetActorTransform(), true);
			ACBGBlock* tempCBGBlock = World->SpawnActor<ACBGBlock>(GetClass(), GetActorLocation(), GetActorRotation(), SpawnParameter);
			tempCBGBlock->SetInitProperty(BlockProperty);
		}
}

void ABlockBase::ApplyPointDamage(AMyCharacter* Causer, int32 DamageValue)
{
	if (BlockProperty.LifeValue <= 0)
	{
		BeBreak();
		return;
	}
	if (BlockProperty.ToMinerBUFF.NotEmpty)
	{
		Causer->AddBUFF(BlockProperty.ToMinerBUFF);
	}
	BlockProperty.LifeValue -= DamageValue;
	return;
}

