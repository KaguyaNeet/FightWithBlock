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


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool AllowMove = true;

	UFUNCTION(reliable, Client, WithValidation, BlueprintCallable)
		void ClientSetAllowInput(bool Choose);
	UFUNCTION(BlueprintImplementableEvent)
		void SetAllowInput(bool Choose);

	UFUNCTION(BlueprintImplementableEvent)
		void RefreshLifeBar_();

	UFUNCTION(reliable, NetMulticast, WithValidation)
		void MulticastRefreshLifeBar();

	void RefreshLifeBar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		FName CharacterName;
	//UFUNCTION(reliable, server, WithValidation)
	//	void ServerSetName(FName Name_);
	//UFUNCTION(BlueprintCallable)
	//	void SetName(FName Name_);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		class UCameraComponent* MyCamera;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* FPSMesh;

	UPROPERTY(VisibleAnywhere)
		class UCharacterMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
		class UArrowComponent* MineTraceStartArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camp", Replicated)
		ECamp MyCamp = ECamp::EDefault;

	bool IsChooseCamp = false;




		FHero HeroInitProperty;

		UPROPERTY(Replicated)
			FItem Bag[BAGSPACE];

		UFUNCTION(reliable, client, WithValidation)
			void ClientAddBlockUI(int Choose, FBlock Item);
		UFUNCTION(reliable, client, WithValidation)
			void ClientRemoveBlockUI(int Choose);


		UFUNCTION(BlueprintImplementableEvent)
			void AddBlockUI(int ChooseNum, FBlock ChangeBlcok);
		UFUNCTION(BlueprintImplementableEvent)
			void RemoveBlockUI(int ChooseNum);
		UFUNCTION(BlueprintImplementableEvent)
			void NowChooseUI(int NowChoose);

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
		UFUNCTION(BlueprintImplementableEvent)
			void PrintRole();

		UFUNCTION(BlueprintImplementableEvent)
			void BlueprintMineBlock();

protected:
	// Called when the game starts or when spawned


	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	UFUNCTION(reliable, Server, WithValidation, BlueprintCallable)
		void ServerSetSpeed(float Speed);
	UFUNCTION(reliable, NetMulticast, WithValidation)
		void MulticastSetSpeed(float Speed);

	bool AddItem(FBlock Item);

	void chooseItem_1();
	void chooseItem_2();
	void chooseItem_3();

	UFUNCTION(reliable, NetMulticast, WithValidation)
		void MulticastReBorn();
	void ReBorn();
	UFUNCTION(reliable, server, WithValidation)
		void ServerSetCamp(ECamp Camp);
	void SetCamp(ECamp Camp);

	UFUNCTION(reliable, server, WithValidation)
		void  ServerChooseItem_1();
	UFUNCTION(reliable, server, WithValidation)
		void  ServerChooseItem_2();
	UFUNCTION(reliable, server, WithValidation)
		void  ServerChooseItem_3();

	UFUNCTION(BlueprintImplementableEvent)
		void BlueprintFire();
	UFUNCTION(BlueprintCallable)
		void Fire_();
	void Fire();
	UFUNCTION(reliable, server, WithValidation)
		void ServerFire();
	UFUNCTION(reliable, NetMulticast, WithValidation)
		void MulticastFire();

	UFUNCTION(reliable, NetMulticast, WithValidation, BlueprintCallable)
		void MulticastSpawnEmitter(UParticleSystem* Particle, FVector Location);
	UFUNCTION(reliable, NetMulticast, WithValidation, BlueprintCallable)
		void MulticastPlayAudio(USoundBase* Sound, FVector Location);

	void SetCameraRotation(FRotator Rotation);
	void SetCamera();
	UFUNCTION(reliable, server, WithValidation)
		void ServerSetCamera(FRotator Rotation);

	UFUNCTION(reliable, NetMulticast, WithValidation)
		void MulticastShakeCamera();
	UFUNCTION(BlueprintImplementableEvent)
		void ShakeCamera();

	FItem* handBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* Hit1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
		UParticleSystem* Hit2;
	UFUNCTION(BlueprintImplementableEvent)
		void BlueprintSpawmEmitter();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isAuth = false;


	void Released_R();
	void PrintItem(FBlock BlockProperty);

	void MineBlock_();
	void MineBlock();
	UFUNCTION(reliable, server, WithValidation)
		void ServerMineBlock();
	UFUNCTION(reliable, NetMulticast, WithValidation)
		void MulticastMineBlock();

	UFUNCTION(BlueprintCallable)
		void MineLineTraceResult(const FHitResult& Hit);
	
	void ApplyPointDamage_(AMyCharacter* Causer, int32 DamageValue);
	void ApplyPointDamage(AMyCharacter* Causer, int32 DamageValue);
	UFUNCTION(reliable, server, WithValidation)
		void ServerApplyPointDamage(AMyCharacter* Causer, int32 DamageValue);

	UFUNCTION(reliable, NetMulticast, WithValidation)
		void ClientDeath();
	void Death(AMyCharacter* Causer);

	void AddBlockToPre(ACBGBlock* Block);
	void RemoveBlockFromPre(ACBGBlock* Block);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
		FHero HeroProperty;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NowChoose = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		bool IsCampFull = true;

	void ControllerInit(ECamp Camp, FString Name);


private:

	FVector GetFireLocation();
	FRotator GetFireRotation();
	
	void SetNowChoose(int Choose);

	UPROPERTY(Replicated)
		TArray<FBUFF> myBUFF;

	bool Keyboard_F_Pressed = false;

	float MineTimeCounter = 0;

	ACBGBlock* printBlock[3] = {NULL};

};
