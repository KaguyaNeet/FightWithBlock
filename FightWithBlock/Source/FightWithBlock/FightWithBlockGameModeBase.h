// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "FightWithBlockGameModeBase.generated.h"

const int32 BAGSPACE = 1;

/**
 * 
 */
UCLASS()
class FIGHTWITHBLOCK_API AFightWithBlockGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
public:
	void PrintKillMessage(class AMyCharacter* Killer, class AMyCharacter* beKiller);
	
};
