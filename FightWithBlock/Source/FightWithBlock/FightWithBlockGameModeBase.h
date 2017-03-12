// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "FightWithBlockGameModeBase.generated.h"

const int32 BAGSPACE = 1;
const int32 WarningSize = 100;

/**
 * 
 */
UCLASS()
class FIGHTWITHBLOCK_API AFightWithBlockGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	//bian chang wei duo shao ge block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 MapSize = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 BlockSize = 260;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 MaxZ = 1;



	
public:

	AFightWithBlockGameModeBase();

	void PrintKillMessage(class AMyCharacter* Killer, class AMyCharacter* beKiller);

	void GenerateGround();

	class ABlockBase* SpawnBlock(const struct FBlock* Block, float Size);
protected:


	virtual void BeginPlay() override;

private:

	TArray<class ABlockBase*> AllBlockInfo;

	TArray<FName> GroundRowNames;
	TArray<FName> SurfaceRowNames;

	UDataTable* GroundDataTable;
	UDataTable* SurfaceDataTable;

};
