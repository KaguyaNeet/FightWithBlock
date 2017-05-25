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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetInitProperty(FBlock Block,class AMyCharacter* Owner_);

	UFUNCTION()
		void OnRep_Init();
	UFUNCTION()
		void OnRep_Explosion();

	//void SetFireDirection(const FVector& Direction, float DropForce);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit);
	
	UPROPERTY(Replicated)
		FBlock BlockProperty;

	void Explosion();
	void BeBreak();

	TSubclassOf<class APoisonCPP> PoisonClass;

private:

	UPROPERTY(ReplicatedUsing = OnRep_Init)
		bool IsInit = false;
	UPROPERTY(ReplicatedUsing = OnRep_Explosion)
		bool IsExplosion = false;
	bool bExplosion = false;
	bool bBreak = false;
	class AMyCharacter* Owner;

};
