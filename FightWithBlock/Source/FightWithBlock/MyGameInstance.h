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

	class AMyPlayerController* PlayerControllers[MaxPlayerNum];
	int NowPlayerNum = 0;
	int ReadyPlayerNum = 0;
	int AlivePlayerNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EGameState GameState = EGameState::ENormal;

	bool AddController(class AMyPlayerController* Controller);
	void AddNowPlayerNum();
	void AddReadyPlayerNum();
	void CheckGameStart();
	void ApplyKill(FName Name_, class AMyPlayerController* Controller);
	void PlayerControllerAddNum();
	void Winner(class AMyPlayerController* Controller);

	UFUNCTION(BlueprintCallable)
		void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
		void Second_3_Delay();
	UFUNCTION(BlueprintCallable)
		void CharacterMove();
	UFUNCTION(BlueprintImplementableEvent)
		void ReadyGameStart();
	UFUNCTION(BlueprintCallable)
		void GameReady();
	UFUNCTION(BlueprintImplementableEvent)
		void WaitTimeGameStart();
	UFUNCTION(BlueprintCallable)
		void InitControllers();
private:

};
