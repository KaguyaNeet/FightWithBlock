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
	

private:


};
