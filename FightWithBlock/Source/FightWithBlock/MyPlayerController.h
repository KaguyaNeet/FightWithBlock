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

	UFUNCTION(reliable, server, WithValidation)
		void SpawnCharacter();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefaultValue")
		FVector RedLocation = FVector(0,0,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefalutValue")
		FVector BlueLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefalutValue")
		ECamp MyCamp = ECamp::EDefault;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyPawn")
		class AMyCharacter* ControllerPawn;

	void SetCamp(ECamp Camp);
};
