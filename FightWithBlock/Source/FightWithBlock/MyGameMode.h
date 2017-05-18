// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"


const int32 BAGSPACE = 3;
const int32 WarningSize = 100;
const int32 MaxPlayerNum = 4;
/**
 * 
 */
UCLASS()
class FIGHTWITHBLOCK_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	//bian chang wei duo shao ge block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 MapSize = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 BlockSize = 260;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 MaxZ = 1;




public:

	AMyGameMode();

	void PrintKillMessage(class AMyCharacter* Killer, class AMyCharacter* beKiller);

	void GenerateGround_();
	void GenerateGround();
	UFUNCTION(reliable, NetMulticast, WithValidation)
		void MulticastGenerateGround();

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
