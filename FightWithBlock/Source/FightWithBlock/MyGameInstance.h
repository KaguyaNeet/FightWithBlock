// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameMode.h"
#include "MyEnums.h"
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

	UFUNCTION(BlueprintCallable)
		int GetGamePlayerNum();
	UFUNCTION(BlueprintCallable)
		int GetReadyPlayerNum();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class APlayerController* Controller = NULL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsGameStart = false;

	void GameStart();
	
	void InitCampInfo();
	void ApplyKill(ECamp Camp);

	int32 RedCampNum = MaxPlayerNum / 2;
	int32 BlueCampNum = MaxPlayerNum / 2;

	class AMyPlayerController* RedCampControllers[MaxPlayerNum / 2];
	class AMyPlayerController* BlueCampControllers[MaxPlayerNum / 2];
	class AMyPlayerController* Controllers[MaxPlayerNum];

	bool IsRedCampFull();
	bool IsBlueCampFull();

	bool RedCampAddController(class AMyPlayerController* Controller);
	bool BlueCampAddController(class AMyPlayerController* Controller);
	bool AddController(class AMyPlayerController* Controller);
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Replicated)
		int ReadyPlayerNum = 0;
private:
	
	void AddReadyPlayer();
	
	void GameReady();
};
