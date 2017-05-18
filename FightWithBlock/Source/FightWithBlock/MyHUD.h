// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTWITHBLOCK_API AMyHUD : public AHUD
{
	GENERATED_BODY()

		AMyHUD();

	virtual void BeginPlay() override;
	
};
