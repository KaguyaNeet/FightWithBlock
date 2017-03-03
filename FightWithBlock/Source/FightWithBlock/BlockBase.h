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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InitProperty")
		FBlock BlockInitProperty;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BeBreak();
	
};
