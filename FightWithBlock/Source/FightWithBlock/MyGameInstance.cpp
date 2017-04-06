// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyGameInstance.h"



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