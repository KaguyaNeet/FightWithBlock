// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "BoltBlock.h"
#include "MyCharacter.h"
#include "BlockBase.h"


// Sets default values
ABoltBlock::ABoltBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	StaticMesh->SetStaticMesh(CubeMesh.Object);
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
	BlockProperty = Block;
	Owner = Owner_;
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	UGameplayStatics::SpawnEmitterAttached(BlockProperty.traceParticle, StaticMesh);
	ProjectileMovement->InitialSpeed = BlockProperty.InitialSpeed;
	ProjectileMovement->MaxSpeed = BlockProperty.InitialSpeed;
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
		HitEnemy->ApplyPointDamage(Owner, BlockProperty.ExplosionDamageValue);
		if (BlockProperty.ToEnemyBUFF.NotEmpty)
		{
			HitEnemy->AddBUFF(BlockProperty.ToEnemyBUFF);
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
	this->Destroy(true);
}

