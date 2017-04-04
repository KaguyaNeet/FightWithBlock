// Fill out your copyright notice in the Description page of Project Settings.

#include "MyStructs.h"
#include "MyGameMode.h"
#include "BoltBlock.h"
#include "CBGBlock.h"
#include "MyEnums.h"

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

	UPROPERTY(VisibleAnywhere, Replicated)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* FPSMesh;

	UPROPERTY(VisibleAnywhere)
		class UCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
		class UArrowComponent* MineTraceStartArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated,Category = "Camp")
		ECamp MyCamp = ECamp::EDefault;

		FHero HeroInitProperty;

		UPROPERTY(Replicated)
			FItem Bag[BAGSPACE];

		void AddUI();

		UFUNCTION(BlueprintImplementableEvent)
			void ChooseHUDLifeValue(float percent);
		UFUNCTION(BlueprintImplementableEvent)
			void CreateUI();
		UFUNCTION(BlueprintImplementableEvent)
			void CreateLifeBar();
		UFUNCTION(BlueprintImplementableEvent)
			void ChooseUILife(float percent);
		UFUNCTION(BlueprintImplementableEvent)
			void ChooseLifeBar(float percent);
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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	bool AddItem(FBlock Item);

	void chooseItem_1();
	void chooseItem_2();
	void chooseItem_3();

	void Fire_();
	void Fire();
	UFUNCTION(reliable, server, WithValidation)
		void ServerFire();

	void SetCameraRotation(FRotator Rotation);
	void SetCamera();
	UFUNCTION(reliable, server, WithValidation)
		void ServerSetCamera(FRotator Rotation);

	FItem* handBlock;

	void AddBUFF(FBUFF BUFF);
	void RunBUFF(float DeltaTime);
	void EndBUFF(int i);
	void ReloadProperty();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	void Pressed_R_();
	void Pressed_R();
	UFUNCTION(reliable, server, WithValidation)
		void ServerPressed_R();



	void Released_R();
	void PrintItem(FBlock BlockProperty);

	void MineBlock_();
	void MineBlock();
	UFUNCTION(reliable, server, WithValidation)
		void ServerMineBlock();

	void MineLineTraceResult(const FHitResult& Hit);
	
	void ApplyPointDamage_(AMyCharacter* Causer, int32 DamageValue);
	void ApplyPointDamage(AMyCharacter* Causer, int32 DamageValue);
	UFUNCTION(reliable, server, WithValidation)
		void ServerApplyPointDamage(AMyCharacter* Causer, int32 DamageValue);


	void Death(AMyCharacter* Causer);

	void AddBlockToPre(ACBGBlock* Block);
	void RemoveBlockFromPre(ACBGBlock* Block);


private:

	FVector GetFireLocation();
	FRotator GetFireRotation();

	UPROPERTY(Replicated)
		TArray<FBUFF> myBUFF;
	UPROPERTY(Replicated)
		FHero HeroProperty;

	bool Keyboard_F_Pressed = false;

	float MineTimeCounter = 0;

	ACBGBlock* printBlock[3] = {NULL};

};
