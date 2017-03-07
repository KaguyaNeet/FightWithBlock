// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "BoltBlock.h"
#include "MyCharacter.h"


// Sets default values
ABoltBlock::ABoltBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetMobility(EComponentMobility::Movable);

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->OnComponentHit.__Internal_AddDynamic(this, &ABoltBlock::OnHit, TEXT("OnHit"));

	ExplosionCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionComponent"));
	ExplosionCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->SetUpdatedComponent(CollisionComponent);
	ProjectileMovement->InitialSpeed = 3000.f;
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
	Owner = Owner;
}

void ABoltBlock::SetFireDirection(const FVector& Direction)
{
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
}

void ABoltBlock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpsule, const FHitResult& Hit)
{
	AMyCharacter* HitEnemy = Cast<AMyCharacter>(OtherActor);
	if (HitEnemy && HitEnemy->MyCamp != Owner->MyCamp)
	{
		HitEnemy->ApplyPointDamage(Owner, BlockProperty.DamageValue);
		Explosion();
	}
	else
	{
		Explosion();
	}
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

void ABoltBlock::BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
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
}

void ABoltBlock::BeBreak()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlockProperty.explosionParticle, FTransform(FRotator(0.f, 0.f, 0.f), GetActorLocation(), FVector(1, 1, 1)));
	this->Destroy(true);
}

