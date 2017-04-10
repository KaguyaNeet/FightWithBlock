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

	UFUNCTION(reliable, NetMulticast, WithValidation)
		void ServerSpawnCharacter();
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnCharacter();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefaultValue")
		FVector RedLocation = FVector(0,0,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefalutValue")
		FVector BlueLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefalutValue")
		ECamp MyCamp = ECamp::EDefault;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		bool IsCampFull = true;
	bool IsChooseCamp = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyPawn")
		class APawn* ControllerPawn;



	void SetCamp(ECamp Camp);

	void InitCharacter();

	UFUNCTION(BlueprintCallable)
		void ChooseCamp(ECamp MyChoose);

	UFUNCTION(reliable, server, WithValidation)
		void ServerChooseCamp(ECamp MyChoose);
	

private:


};
