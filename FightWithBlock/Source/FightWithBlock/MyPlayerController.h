// Fill out your copyright notice in the Description page of Project Settings.
#include "MyEnums.h"

#pragma once

#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTWITHBLOCK_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMyPlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;
	UFUNCTION(BlueprintCallable)
		void ServerSpawnCharacter();
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnCharacter();

	UFUNCTION(reliable, NetMulticast, WithValidation)
		void PrintCamp();

	void AddController();

	UFUNCTION(BlueprintImplementableEvent)
		void Test();

	UFUNCTION(BlueprintImplementableEvent)
		void PrintRole(ENetRole nowRole, int count);

	UFUNCTION(BlueprintCallable)
		void BlueprintSpawnCharacter();

	UFUNCTION(reliable, client, WithValidation, BlueprintCallable)
		void SetPosses();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerNum", Replicated)
		int32 PlayerNum = 0;

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefaultValue")
		FVector RedLocation = FVector(0,0,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefalutValue")
		FVector BlueLocation = FVector(0,0,0);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefalutValue", Replicated)
		ECamp MyCamp = ECamp::EDefault;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		bool IsCampFull = true;
	bool IsChooseCamp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefalutValue", Replicated)
		FName MyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyPawn", Replicated)
		class APawn* ControllerPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameState", Replicated)
		EGameState MyGameState = EGameState::ENormal;


	void InitCharacter();

	UFUNCTION(BlueprintImplementableEvent)
		void CheckMap(ENetRole thisRole);

	UFUNCTION(reliable, Client, WithValidation)
		void ClientCheckMap(ENetRole thisRole);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Role")
		bool isServer = false;

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnMoxing();

	UFUNCTION(BlueprintCallable, reliable, Server, WithValidation)
		void ServerSetName(FName Name_);

	UFUNCTION(BlueprintCallable, reliable, Server, WithValidation)
		void ServerSetzhanlan();
	UFUNCTION(BlueprintImplementableEvent)
		void Setzhanlan();

	UFUNCTION(BlueprintImplementableEvent)
		void ControllerReady();

	UFUNCTION(reliable, Client, WithValidation)
		void ServerControllerReady();

	void PlayerReady();
	void PlayerStart();

	UFUNCTION(reliable, Client, WithValidation)
		void ClientEndText();
	UFUNCTION(BlueprintImplementableEvent)
		void EndText();

	UFUNCTION(reliable, Server, WithValidation)
		void ServerCharacterDeath();
	void CharacterDeath();

	UFUNCTION(reliable, Client, WithValidation)
		void ClientPrintKillMessage(FName Name);
	UFUNCTION(BlueprintImplementableEvent)
		void PrintKillMessage(FName Name);

	bool isDeath = false;

	UFUNCTION(reliable, Client, WithValidation)
		void ClientTargetMoveToWinner(AMyPlayerController* Controller);
	UFUNCTION(BlueprintImplementableEvent)
		void TargetMoveToWinner(AMyPlayerController* Controller);
	UFUNCTION(reliable, Server, WithValidation)
		void ServerSetAllowInput(bool Choose);
	UFUNCTION(BlueprintImplementableEvent)
		void SetAllowInput(bool Choose);
	UFUNCTION(reliable, Client, WithValidation)
		void ClientAddStartMessage();
	UFUNCTION(BlueprintImplementableEvent)
		void AddStartMessage();
	//UFUNCTION(reliable, Client, WithValidation)
	//	void ClientSetName();

private:


};
