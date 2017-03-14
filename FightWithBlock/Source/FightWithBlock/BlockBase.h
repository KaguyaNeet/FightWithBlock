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

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMesh;	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BeBreak();

	void SetInitProperty(FBlock Block);

	void ApplyPointDamage(class AMyCharacter* Causer, int32 DamageValue);

private:

	FBlock BlockProperty;

	float AddBUFFRateTime = 5.f;
	float AddBUFFTimeCounter = 0.f;
	bool AddBUFF = true;

	void BUFFTimeCounter(float DeltaTime);
	
};