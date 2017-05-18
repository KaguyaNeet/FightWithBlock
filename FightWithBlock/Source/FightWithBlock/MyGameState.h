// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTWITHBLOCK_API AMyGameState : public AGameState
{
	GENERATED_BODY()


		AMyGameState();
	UPROPERTY(EditAnywhere, Category = "MapProperty")
		int32 MapSize = 2;
	UPROPERTY(EditAnywhere, Category = "MapProperty")
		int32 BlockSize = 260;
	UPROPERTY(EditAnywhere, Category = "MapProperty")
		int32 MaxZ = 1;
	
	void GenerateGround_();
	void GenerateGround();
	UFUNCTION(reliable, NetMulticast, WithValidation)
		void ServerGenerateGround();

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
