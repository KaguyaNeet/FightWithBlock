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
	if (StaticMesh->GetBodyInstance())
	{
		StaticMesh->GetBodyInstance()->bLockXTranslation = true;
		StaticMesh->GetBodyInstance()->bLockYTranslation = true;
		StaticMesh->GetBodyInstance()->bLockXRotation = true;
		StaticMesh->GetBodyInstance()->bLockYRotation = true;
		StaticMesh->GetBodyInstance()->bLockZRotation = true;
	}
	StaticMesh->SetMobility(EComponentMobility::Static);

	BlockProperty.LifeValue = 3;
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
			//TMD就是这里出的问题。。我感觉是那个GetClass(),绝壁有问题，但我不知道怎么改啊 我能怎么办 我也很绝望啊，怎么得到ACBGBlock的class嘛 非得重新声明一个吗！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
			//ACBGBlock temp;
			ACBGBlock* tempCBGBlock = World->SpawnActor<ACBGBlock>(GetActorLocation(), GetActorRotation(), SpawnParameter);
			tempCBGBlock->SetInitProperty(BlockProperty);
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
		//引人注意！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
		//BeBreak()有问题 目前没有解决 调用的时候会导致崩溃 艹！
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

