// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"



UMyGameInstance::UMyGameInstance()
{
	//UWorld* World = GetWorld();
	//AGameModeBase* MyGameMode = UGameplayStatics::GetGameMode(World);
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		PlayerControllers[i] = NULL;
	}
}

bool UMyGameInstance::AddController(AMyPlayerController* Controller)
{
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		if (PlayerControllers[i] == NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Add++++++++++++"));
			PlayerControllers[i] = Controller;
			PlayerControllers[i]->SpawnMoxing(); 
			AddNowPlayerNum();
			PlayerControllerAddNum();
			return true;
		}
	}
	return false;
}

void UMyGameInstance::AddNowPlayerNum()
{
	NowPlayerNum++;
	AddReadyPlayerNum();
}

void UMyGameInstance::AddReadyPlayerNum()
{
	ReadyPlayerNum++;
	CheckGameStart();
}

void UMyGameInstance::CheckGameStart()
{
	if (ReadyPlayerNum == NowPlayerNum)
	{

	}
}

void UMyGameInstance::GameReady()
{
	GameState = EGameState::EReady;
}

void UMyGameInstance::ApplyKill()
{

}

void UMyGameInstance::PlayerControllerAddNum()
{
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		if (PlayerControllers[i] != NULL)
		{
			PlayerControllers[i]->PlayerNum = NowPlayerNum;
		}
		else
		{
			return;
		}
	}
}