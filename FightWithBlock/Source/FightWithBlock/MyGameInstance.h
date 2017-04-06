// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameMode.h"
#pragma once

#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTWITHBLOCK_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

		UMyGameInstance();
	
public:

	int GetGamePlayerNum();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsGameStart = false;

	class AMyCharacter* RedCampCharacters[MaxPlayerNum / 2];
	class AMyCharacter* BlueCampCharacters[MaxPlayerNum / 2];

	bool IsRedCampFull();
	bool IsBlueCampFull();
};
