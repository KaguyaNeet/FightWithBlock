// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PoisonCPP.generated.h"

UCLASS()
class FIGHTWITHBLOCK_API APoisonCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoisonCPP();

	UFUNCTION(BlueprintImplementableEvent)
		void BlueprintDelayDestroy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
