// Fill out your copyright notice in the Description page of Project Settings.
#include "MyStructs.h"
#pragma once

#include "GameFramework/Actor.h"
#include "CBGBlock.generated.h"
//���Ǵ��鷽�� ���ɵĿ�ʰȡ�ķ��� ���ڵ��ϸ���

UCLASS()
class FIGHTWITHBLOCK_API ACBGBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBGBlock();

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* CollisionComponent;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void floatUpDown();

	void SetInitProperty(FBlock Block);

	void DestroySelf();

	FBlock BlockProperty;
};
