// Fill out your copyright notice in the Description page of Project Settings.

#include "MyStructs.h"
#include "FightWithBlockGameModeBase.h"
#include "BoltBlock.h"
#include "CBGBlock.h"

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class FIGHTWITHBLOCK_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* FPSMesh;

	UPROPERTY(VisibleAnywhere)
		class UCharacterMovementComponent* MovementComponent;

		FHero HeroInitProperty;

		FItem Bag[BAGSPACE];





protected:
	// Called when the game starts or when spawned


	virtual void BeginPlay() override;

	void MoveForward(float val);

	void MoveRight(float val);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool AddItem(FBlock Item);

	void chooseItem_1();
	void chooseItem_2();
	void chooseItem_3();

	void Fire();

	FItem handBlock;

	void AddBUFF(FBUFF BUFF);
	void RunBUFF(float DeltaTime);
	void EndBUFF(int i);
	void ReloadProperty();

	void BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit);

	void Pressed_R();
	void Released_R();
	void PrintItem(FBlock BlockProperty);

private:

	FVector GetFireLocation();
	FRotator GetFireRotation();

	TArray<FBUFF> myBUFF;
	FHero HeroProperty;

	bool Keyboard_F_Pressed = false;
};
