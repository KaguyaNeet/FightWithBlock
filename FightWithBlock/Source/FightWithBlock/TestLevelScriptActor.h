// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "TestLevelScriptActor.generated.h"

/**
 * 
 */

const float DSize = 0.61;
UCLASS()
class FIGHTWITHBLOCK_API ATestLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

		ATestLevelScriptActor();
	
public:
	//bian chang wei duo shao ge block
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 MapSize = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 BlockSize = 95;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MapProperty")
		int32 MaxZ = 1;

	UFUNCTION(BlueprintImplementableEvent)
		void Loading();

	UFUNCTION(BlueprintImplementableEvent)
		void print();
	UFUNCTION(BlueprintCallable)
		void CreateMap();

	UFUNCTION(BlueprintCallable)
		void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
		void StartInit();
	UFUNCTION(BlueprintImplementableEvent)
		void CheckReady();
	//UFUNCTION(reliable, NetMulticast, WithValidation)
	//	void MulticastAddLoadingUI();



public:

	//void PrintKillMessage(class AMyCharacter* Killer, class AMyCharacter* beKiller);

	void GenerateGround();

	void GenerateGroundWall();

	void GenerateWall();

	void ReadHeightMap();


	class ABlockBase* SpawnBlock(const struct FBlock Block, float Size);
protected:


	virtual void BeginPlay() override;

	

private:
	int32 WarningSize = 100;
	TArray<class ABlockBase*> AllBlockInfo;

	TArray<FName> GroundRowNames;
	TArray<FName> SurfaceRowNames;

	UDataTable* GroundDataTable;
	UDataTable* SurfaceDataTable;

	UDataTable* WallDataTable;
	TArray<FName> WallRowNames;

	UTexture2D* HeightFile = NULL;

	void GenerateWall_x(int z, FBlock Block);
	void GenerateWall_y(int z, FBlock Block);
	void GenerateWall_Corner(int z, FBlock Block);

};
