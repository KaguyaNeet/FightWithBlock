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
			PlayerControllers[i]->Controller_ID = NowPlayerNum;
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
	AlivePlayerNum = NowPlayerNum;
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
	Controller->isDeath = true;
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
	Second_3_Delay();
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		if (PlayerControllers[i] != NULL)
		{
			PlayerControllers[i]->PlayerReady();
		}
		else
		{
			return;
		}
	}
}

void UMyGameInstance::CharacterMove()
{
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		if (PlayerControllers[i] != NULL)
		{
			PlayerControllers[i]->PlayerStart();
		}
	}
}

void UMyGameInstance::Winner(AMyPlayerController* Controller)
{
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		if (PlayerControllers[i] != NULL)
		{
			if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(PlayerControllers[i]->GetControlledPawn()))
			{
				MyCharacter->ClientSetAllowInput(false);
			}
			PlayerControllers[i]->TargetMoveToWinner(Controller);
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Winner!!!!!!!!!!!!!!!"));
		}
	}
}

void UMyGameInstance::InitControllers()
{
	for (int i = 0; i < MaxPlayerNum; i++)
	{
		PlayerControllers[i] = NULL;
	}
	NowPlayerNum = 0;
	ReadyPlayerNum = 0;
	AlivePlayerNum = 0;
	GameState = EGameState::ENormal;
}