// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyGameInstance.h"
#include "MyCharacter.h"


UMyGameInstance::UMyGameInstance()
{
	//UWorld* World = GetWorld();
	//AGameModeBase* MyGameMode = UGameplayStatics::GetGameMode(World);
	for (int i = 0; i < MaxPlayerNum / 2; i++)
	{
		RedCampCharacters[i] = NULL;
		BlueCampCharacters[i] = NULL;
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
		if (RedCampCharacters[i] == NULL)
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
		if (BlueCampCharacters[i] == NULL)
		{
			return false;
		}
	}
	return true;
}

bool UMyGameInstance::RedCampAdd(AMyCharacter* Character)
{
	if (IsRedCampFull())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("ย๚มห"));
		return false;
	}
	else
	{
		for (int i = 0; i < MaxPlayerNum / 2; i++)
		{
			if (RedCampCharacters[i] == NULL)
			{
				RedCampCharacters[i] = Character;
				AddReadyPlayer();
				//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("Add"));
				return true;
			}
		}
		return false;
	}
}

bool UMyGameInstance::BlueCampAdd(AMyCharacter* Character)
{
	if (IsBlueCampFull())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < MaxPlayerNum / 2; i++)
		{
			if (BlueCampCharacters[i] == NULL)
			{
				BlueCampCharacters[i] = Character;
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
	}
	if (ReadyPlayerNum == GetGamePlayerNum())
	{
		GameStart();
	}
}

void UMyGameInstance::GameStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("GameStart!!!!!!!!!!!!!"));
	for (int i = 0; i < MaxPlayerNum / 2; i++)
	{
		RedCampCharacters[i]->RefreshLifeBar();
		BlueCampCharacters[i]->RefreshLifeBar();
	}
}