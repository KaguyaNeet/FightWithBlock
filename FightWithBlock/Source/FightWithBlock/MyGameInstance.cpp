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
			//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Add++++++++++++"));
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
	WaitTimeGameStart();
	GameState = EGameState::EReady;
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		if (PlayerControllers[i] != NULL)
		{
			PlayerControllers[i]->ServerControllerReady();
		}
		else
		{
			return;
		}
	}
}

void UMyGameInstance::ApplyKill(FName Name, AMyPlayerController* Controller)
{
	AlivePlayerNum--;
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		if (PlayerControllers[i] != NULL)
		{
			PlayerControllers[i]->ClientPrintKillMessage(Name);
		}
		else
		{
			break;
		}
	}
	if (AlivePlayerNum == 1)
	{
		for (int i = 0; i < MaxPlayerNum; i++)
		{
			if (PlayerControllers[i] != NULL && PlayerControllers[i]->isDeath == false)
			{
				Winner(PlayerControllers[i]);
				return;
			}
		}
	}
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

void UMyGameInstance::GameStart()
{
	AlivePlayerNum = NowPlayerNum;
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("GameStart"));
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		if (PlayerControllers[i] != NULL)
		{
			PlayerControllers[i]->PlayerStart();
		}
		else
		{
			return;
		}
	}
}

void UMyGameInstance::Winner(AMyPlayerController* Controller)
{
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		if (PlayerControllers[i] != NULL)
		{
			PlayerControllers[i]->TargetMoveToWinner(Controller);
		}
	}
}