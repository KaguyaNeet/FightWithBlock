// Fill out your copyright notice in the Description page of Project Settings.
#include "MyStructs.h"

#pragma once



#include "GameFramework/Actor.h"
#include "BlockBase.generated.h"


UCLASS()
class FIGHTWITHBLOCK_API ABlockBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockBase();

	UPROPERTY(VisibleAnywhere, Replicated)
		class UStaticMeshComponent* StaticMesh;	

	UFUNCTION(reliable, NetMulticast, WithValidation, BlueprintCallable)
		void MulticastPlayAudio(USoundBase* Sound, FVector Location);

	USoundBase* BreakSound;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BeBreak();

	void SetInitProperty(FBlock Block);

	void ApplyPointDamage(class AMyCharacter* Causer, int32 DamageValue);

	void DestroySelf();

	UFUNCTION()
		void OnRep_ReplicateInit();
	UFUNCTION()
		void OnRep_Break();
	UFUNCTION()
		void OnRep_Destroy();

	

private:
	UPROPERTY(Replicated)
		FBlock BlockProperty;
	UPROPERTY(Replicated)
		UStaticMesh* Mesh;
	UPROPERTY(Replicated)
		UMaterial* Material;
	UPROPERTY(Replicated)
		UParticleSystem* selfParticle;
	UPROPERTY(ReplicatedUsing = OnRep_ReplicateInit)
		bool Init = false;
	UPROPERTY(ReplicatedUsing = OnRep_Break)
		bool IsBreak = false;
	UPROPERTY(ReplicatedUsing = OnRep_Destroy)
		bool IsDestroy = false;
	float AddBUFFRateTime = 5.f;
	float AddBUFFTimeCounter = 0.f;
	bool AddBUFF = true;

	void BUFFTimeCounter(float DeltaTime);
	
};