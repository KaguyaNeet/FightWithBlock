// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "TestLevelScriptActor.generated.h"

/**
 * 
 */

const float DSize = 0.4;
UCLASS()
class FIGHTWITHBLOCK_API ATestLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

		ATestLevelScriptActor();
	
public:
	//bian chang wei duo shao ge block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 MapSize = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 BlockSize = 260;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 MaxZ = 1;




public:


	//void PrintKillMessage(class AMyCharacter* Killer, class AMyCharacter* beKiller);

	void GenerateGround();


	class ABlockBase* SpawnBlock(const struct FBlock* Block, float Size);
protected:


	virtual void BeginPlay() override;

private:
	int32 WarningSize = 100;
	TArray<class ABlockBase*> AllBlockInfo;

	TArray<FName> GroundRowNames;
	TArray<FName> SurfaceRowNames;

	UDataTable* GroundDataTable;
	UDataTable* SurfaceDataTable;

};
