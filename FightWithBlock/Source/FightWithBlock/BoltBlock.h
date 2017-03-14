// Fill out your copyright notice in the Description page of Project Settings.
#include "MyStructs.h"
#pragma once

#include "GameFramework/Actor.h"
#include "BoltBlock.generated.h"

//就是拿在手上和扔出去的方块

UCLASS()
class FIGHTWITHBLOCK_API ABoltBlock : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABoltBlock();

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* ExplosionCollisionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetInitProperty(FBlock Block,class AMyCharacter* Owner_);

	void SetFireDirection(const FVector& Direction, float DropForce);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit);
	

	FBlock BlockProperty;

	void Explosion();
	void BeBreak();

private:

	bool bExplosion = false;
	class AMyCharacter* Owner;

};
