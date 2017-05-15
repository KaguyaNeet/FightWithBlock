// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"



UMyGameInstance::UMyGameInstance()
{
	//UWorld* World = GetWorld();
	//AGameModeBase* MyGameMode = UGameplayStatics::GetGameMode(World);
	for (int i = 0; i < MaxPlayerNum / 2; i++)
	{
		RedCampControllers[i] = NULL;
		BlueCampControllers[i] = NULL;
	}
}

int UMyGameInstance::GetGamePlayerNum()
{
	return MaxPlayerNum;
}


bool UMyGameInstance::IsRedCampFull()
{
	for (int i = 0; i < MaxPlayerNum / 2; i++)
	{
		if (RedCampControllers[i] == NULL)
		{
			return false;
		}
	}
	return true;
}

bool UMyGameInstance::IsBlueCampFull()
{
	for (int i = 0; i < MaxPlayerNum / 2; i++)
	{
		if (BlueCampControllers[i] == NULL)
		{
			return false;
		}
	}
	return true;
}

bool UMyGameInstance::RedCampAddController(AMyPlayerController* Controller)
{
	if (IsRedCampFull())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < MaxPlayerNum / 2; i++)
		{
			if (RedCampControllers[i] == NULL)
			{
				RedCampControllers[i] = Controller;
				AddReadyPlayer();
				return true;
			}
		}
		return false;
	}
}

bool UMyGameInstance::BlueCampAddController(AMyPlayerController* Controller)
{
	if (IsBlueCampFull())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < MaxPlayerNum / 2; i++)
		{
			if (BlueCampControllers[i] == NULL)
			{
				BlueCampControllers[i] = Controller;
				AddReadyPlayer();
				return true;
			}
		}
		return false;
	}
}


int UMyGameInstance::GetReadyPlayerNum()
{
	return ReadyPlayerNum;
}

void UMyGameInstance::AddReadyPlayer()
{
	if (ReadyPlayerNum < GetGamePlayerNum())
	{
		ReadyPlayerNum++;
		for (int i = 0; i < MaxPlayerNum / 2; i++)
		{
			if (RedCampControllers[i] != NULL)
			{
				RedCampControllers[i]->PlayerNum = ReadyPlayerNum;
			}
			if (BlueCampControllers[i] != NULL)
			{
				BlueCampControllers[i]->PlayerNum = ReadyPlayerNum;
			}
		}
	}
	if (ReadyPlayerNum == GetGamePlayerNum())
	{
		GameReady();
	}
}

void UMyGameInstance::GameStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("GameStart!!!!!!!!!!!!!"));
	InitCampInfo();
	for (int i = 0; i < MaxPlayerNum / 2; i++)
	{
		RedCampControllers[i]->InitCharacter();
		//RedCampControllers[i]->MyGameState = EGameState::ERunning;
		BlueCampControllers[i]->InitCharacter();
		//BlueCampControllers[i]->MyGameState = EGameState::ERunning;
	}
}

void UMyGameInstance::InitCampInfo()
{
	RedCampNum = MaxPlayerNum / 2;
	BlueCampNum = MaxPlayerNum / 2;
}

void UMyGameInstance::ApplyKill(ECamp Camp)
{
	switch (Camp)
	{
	case ECamp::ERed: {
		RedCampNum--;
		break;
	}
	case ECamp::EBlue: {
		BlueCampNum--;
		break;
	}
	default:break;
	}
	if (RedCampNum == 0)
	{
		//GameStart();
	}
	if (BlueCampNum == 0)
	{
		//GameStart();
	}
}

void UMyGameInstance::GameReady()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("GameReady!!!!!!!!!!!!!"));
	InitCampInfo();
	for (int i = 0; i < MaxPlayerNum / 2; i++)
	{
		//RedCampControllers[i]->InitCharacter();
		RedCampControllers[i]->MyGameState = EGameState::ERunning;
		//BlueCampControllers[i]->InitCharacter();
		BlueCampControllers[i]->MyGameState = EGameState::ERunning;
	}
}