// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "BlockBase.h"
#include "MyCharacter.h"

// Sets default values
ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachTo(RootComponent);
	StaticMesh->SetLockedAxis(EDOFMode::Default);
	StaticMesh->SetConstraintMode(EDOFMode::Default);
	StaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempCube(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	StaticMesh->SetStaticMesh(tempCube.Object);



	if (StaticMesh->GetBodyInstance())
	{
		StaticMesh->GetBodyInstance()->bLockXTranslation = true;
		StaticMesh->GetBodyInstance()->bLockYTranslation = true;
		StaticMesh->GetBodyInstance()->bLockXRotation = true;
		StaticMesh->GetBodyInstance()->bLockYRotation = true;
		StaticMesh->GetBodyInstance()->bLockZRotation = true;
	}
	StaticMesh->SetMobility(EComponentMobility::Static);
	//²âÊÔÓÃ£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡
	BlockProperty.LifeValue = 3;
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempFire(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> tempExplosion(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	BlockProperty.selfParticle = tempFire.Object;
	BlockProperty.handParticle = tempFire.Object;
	BlockProperty.traceParticle = tempFire.Object;
	BlockProperty.breakParticle = tempExplosion.Object;
	BlockProperty.explosionParticle = tempExplosion.Object;
	//£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡

	//UGameplayStatics::SpawnEmitterAttached(BlockProperty.selfParticle, StaticMesh);
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

	if (!AddBUFF)
		BUFFTimeCounter(DeltaTime);

}

void ABlockBase::SetInitProperty(FBlock Block)
{
	//BlockProperty = Block;
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
			ACBGBlock* tempCBGBlock = World->SpawnActor<ACBGBlock>(GetActorLocation(), GetActorRotation(), SpawnParameter);
			tempCBGBlock->SetInitProperty(BlockProperty);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlockProperty.breakParticle, GetActorLocation(), GetActorRotation(), true);
			this->Destroy(true);
		}
}

void ABlockBase::ApplyPointDamage(AMyCharacter* Causer, int32 DamageValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ApplyDamage"));
	if (BlockProperty.ToMinerBUFF.NotEmpty)
	{
		if (AddBUFF)
		{
			Causer->AddBUFF(BlockProperty.ToMinerBUFF);
			AddBUFF = false;
		}
	}
	BlockProperty.LifeValue -= DamageValue;
	if (BlockProperty.LifeValue <= 0)
	{
		BeBreak();
		return;
	}
	return;
}

void ABlockBase::BUFFTimeCounter(float DeltaTime)
{
	if(!AddBUFF)
	{
		AddBUFFTimeCounter += DeltaTime;
		if (AddBUFFTimeCounter >= AddBUFFRateTime)
		{
			AddBUFF = true;
			AddBUFFTimeCounter = 0.f;
			return;
		}
	}
	else
	{
		return;
	}
}

