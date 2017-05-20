// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "BlockBase.h"
#include "MyCharacter.h"
#include "Net/UnrealNetwork.h"
#include "TestLevelScriptActor.h"
// Sets default values


ABlockBase::ABlockBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachTo(RootComponent);
	StaticMesh->bCastDynamicShadow = true;
	StaticMesh->SetLockedAxis(EDOFMode::Default);
	StaticMesh->SetConstraintMode(EDOFMode::Default);
	StaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	StaticMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempCube(TEXT("StaticMesh'/Engine/EngineMeshes/Cube.Cube'"));
	StaticMesh->SetStaticMesh(tempCube.Object);

	ConstructorHelpers::FObjectFinder<USoundBase> tempSound(TEXT("SoundWave'/Game/Audio/BreakSound01.BreakSound01'"));
	if (tempSound.Succeeded())
		BreakSound = tempSound.Object;



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
	//BlockProperty.LifeValue = 3;
	//ConstructorHelpers::FObjectFinder<UParticleSystem> tempFire(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	//ConstructorHelpers::FObjectFinder<UParticleSystem> tempExplosion(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));

	//BlockProperty.selfParticle = tempFire.Object;
	//BlockProperty.handParticle = tempFire.Object;
	//BlockProperty.traceParticle = tempFire.Object;
	//BlockProperty.breakParticle = tempExplosion.Object;
	//BlockProperty.explosionParticle = tempExplosion.Object;
	//£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡

	//UGameplayStatics::SpawnEmitterAttached(BlockProperty.selfParticle, StaticMesh);
}

void ABlockBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(ABlockBase, BlockProperty);
	//DOREPLIFETIME(ABlockBase, Size);
	DOREPLIFETIME(ABlockBase, selfParticle);
	DOREPLIFETIME(ABlockBase, Material);
	DOREPLIFETIME(ABlockBase, Mesh);
	DOREPLIFETIME(ABlockBase, Init);
	DOREPLIFETIME(ABlockBase, IsBreak);
	DOREPLIFETIME(ABlockBase, IsDestroy);
	
	//DOREPLIFETIME(ABlockBase, StaticMesh);
	//DOREPLIFETIME(ABlockBase, )
}
// Called when the game starts or when spawned
void ABlockBase::BeginPlay()
{
	Super::BeginPlay();
	//if(Role == ROLE_Authority)
	//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, TEXT("Authority!!!!!!~~~~~~~~~~~~"));
	//if(Role == ROLE_AutonomousProxy)
	//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, TEXT("AutonomousProxy!!!!!!~~~~~~~~~~~~"));
	//if(Role == ROLE_SimulatedProxy)
	//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, TEXT("SimulatedProxy!!!!!!~~~~~~~~~~~~"));
}

// Called every frame
void ABlockBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), BlockProperty.ID);
	if (!AddBUFF)
		BUFFTimeCounter(DeltaTime);
}

void ABlockBase::SetInitProperty(FBlock Block)
{
	//GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, TEXT("Init!!!!!!~~~~~~~~~~~~"));
	Material = Block.Material;
	Mesh = Block.StaticMesh;
	BlockProperty = Block;
	selfParticle = Block.breakParticle;
	StaticMesh->SetStaticMesh(BlockProperty.StaticMesh);
	StaticMesh->SetMaterial(0, BlockProperty.Material);
	UGameplayStatics::SpawnEmitterAttached(BlockProperty.selfParticle, StaticMesh);
	StaticMesh->SetWorldScale3D(FVector(1,1,1) * 0.61f * DSize);
	Init = true;
}
void ABlockBase::OnRep_ReplicateInit()
{
	//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Blue,TEXT("OnRep!!!!!!"));
	if (Init)
	{
		//if(BlockProperty.ID == 0)
		//	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Blue, TEXT("noooooooooooooooo!!!!!!"));
		StaticMesh->SetStaticMesh(Mesh);
		StaticMesh->SetMaterial(0, Material);
		BlockProperty.breakParticle = selfParticle;
		//UGameplayStatics::SpawnEmitterAttached(selfParticle, StaticMesh);
		StaticMesh->SetWorldScale3D(FVector(1, 1, 1) * 0.61f * DSize);
		Init = true;
	}
}
//bool ABlockBase::SetInitProperty_Validate(FBlock Block)
//{
//	return true;
//}
//void ABlockBase::ServerSetInitProperty(FBlock Block)
//{
//
//}
//bool ABlockBase::ServerSetInitProperty_Validate(FBlock Block)
//{
//	return true;
//}

void ABlockBase::BeBreak()
{
	//StaticMesh->SetWorldScale3D(FVector(0, 0, 0));
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡£¡"));
	DestroySelf();
	UWorld* World = GetWorld();
	if (World)
	{
		MulticastPlayAudio(BreakSound, GetActorLocation());
		FActorSpawnParameters SpawnParameter;
		SpawnParameter.Owner = this;
		SpawnParameter.Instigator = Instigator;
		if (BlockProperty.breakParticle && BlockProperty.breakParticle->IsTemplate())
			UGameplayStatics::SpawnEmitterAtLocation(World, BlockProperty.breakParticle, GetActorTransform(), true);
		ACBGBlock* tempCBGBlock = World->SpawnActor<ACBGBlock>(GetActorLocation(), GetActorRotation(), SpawnParameter);
		tempCBGBlock->SetInitProperty(BlockProperty);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlockProperty.breakParticle, GetActorLocation(), GetActorRotation(), true);
	}
}

void ABlockBase::ApplyPointDamage(AMyCharacter* Causer, int32 DamageValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ApplyDamage"));
	if (!BlockProperty.CanNotDestroy)
	{
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
			IsBreak = true;
			BeBreak();
			return;
		}
		return;
	}
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
void ABlockBase::OnRep_Break()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("BreakRep!!!!!!!!!!!"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlockProperty.breakParticle, GetActorLocation(), GetActorRotation(), true);
}
void ABlockBase::DestroySelf()
{
	IsDestroy = true;
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetWorldScale3D(FVector(0, 0, 0));
	
}
void ABlockBase::OnRep_Destroy()
{
	DestroySelf();
}

void ABlockBase::MulticastPlayAudio_Implementation(USoundBase* Sound, FVector Location)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location);
}
bool ABlockBase::MulticastPlayAudio_Validate(USoundBase* Sound, FVector Location)
{
	return true;
}
