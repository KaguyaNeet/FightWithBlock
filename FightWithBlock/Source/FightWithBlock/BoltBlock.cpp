// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "BoltBlock.h"
#include "MyCharacter.h"
#include "BlockBase.h"
#include "NET/UnrealNetwork.h"

// Sets default values
ABoltBlock::ABoltBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bReplicateMovement = true;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);
	RootComponent->SetMobility(EComponentMobility::Movable);
	CollisionComponent->SetWorldScale3D(FVector(1, 1, 1));
	CollisionComponent->SetBoxExtent(FVector(50, 50, 50));
	//CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	//CollisionComponent->OnComponentHit.AddDynamic(this, &ABoltBlock::OnHit);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABoltBlock::BeginOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachTo(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetWorldScale3D(FVector(0.2, 0.2, 0.2));
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	//StaticMesh->SetStaticMesh(CubeMesh.Object);
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



	ExplosionCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionComponent"));
	ExplosionCollisionComponent->AttachTo(RootComponent);
	ExplosionCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(CollisionComponent);
	ProjectileMovement->InitialSpeed = 3000;
	ProjectileMovement->MaxSpeed = 3000;
	ProjectileMovement->bRotationFollowsVelocity = true;


}

void ABoltBlock::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABoltBlock, BlockProperty);
	DOREPLIFETIME(ABoltBlock, IsInit);
	DOREPLIFETIME(ABoltBlock, IsExplosion);
}

void ABoltBlock::OnRep_Init()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, TEXT("RepInit"));
	//CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UGameplayStatics::SpawnEmitterAttached(BlockProperty.traceParticle, StaticMesh);
	//ProjectileMovement->InitialSpeed = BlockProperty.InitialSpeed;
	//ProjectileMovement->MaxSpeed = BlockProperty.InitialSpeed;
	StaticMesh->SetStaticMesh(BlockProperty.StaticMesh);
	StaticMesh->SetMaterial(0, BlockProperty.Material);
	StaticMesh->SetWorldScale3D(StaticMesh->GetComponentScale() * BlockProperty.Size);
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

void ABoltBlock::SetInitProperty(FBlock Block, AMyCharacter* Owner_)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, TEXT("Init"));
	IsInit = true;
	BlockProperty = Block;
	Owner = Owner_;
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UGameplayStatics::SpawnEmitterAttached(BlockProperty.traceParticle, StaticMesh);
	//ProjectileMovement->InitialSpeed = BlockProperty.InitialSpeed;
	//ProjectileMovement->MaxSpeed = BlockProperty.InitialSpeed;
	StaticMesh->SetStaticMesh(BlockProperty.StaticMesh);
	StaticMesh->SetMaterial(0, BlockProperty.Material);
	StaticMesh->SetWorldScale3D(StaticMesh->GetComponentScale() * BlockProperty.Size);
}

void ABoltBlock::SetFireDirection(const FVector& Direction, float DropForce)
{
	//ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
}


void ABoltBlock::Explosion()
{
	if (!bExplosion)
	{
		bExplosion = true;
		ExplosionCollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		ExplosionCollisionComponent->OnComponentBeginOverlap.__Internal_AddDynamic(this, &ABoltBlock::BeginOverlap, TEXT("BeginOverlap"));
		BeBreak();
	}
	else
	{
		BeBreak();
	}
}

void ABoltBlock::BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
{
	AMyCharacter* HitEnemy = Cast<AMyCharacter>(OtherActor);
	if (HitEnemy && HitEnemy->MyCamp != Owner->MyCamp)
	{
		HitEnemy->ApplyPointDamage(Owner, BlockProperty.DamageValue);
		HitEnemy->GetCapsuleComponent()->AddTorque(GetVelocity() * 100);
		Explosion();
		if (BlockProperty.ToEnemyBUFF.NotEmpty)
		{
			HitEnemy->AddBUFF(BlockProperty.ToEnemyBUFF);
			GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, TEXT("addBUFF"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("OtherOverlap"));
		if (OtherComponent->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)
		{
			Explosion();
		}
	}
}

void ABoltBlock::BeBreak()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlockProperty.explosionParticle, FTransform(FRotator(0.f, 0.f, 0.f), GetActorLocation(), FVector(1, 1, 1)));
	StaticMesh->SetWorldScale3D(FVector(0, 0, 0));
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	IsExplosion = true;
	//this->Destroy(true);
}
void ABoltBlock::OnRep_Explosion()
{
	BeBreak();
}

