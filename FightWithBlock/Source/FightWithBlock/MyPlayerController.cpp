// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "MyGameInstance.h"
#include "NET/UnrealNetwork.h"

static int counter = 0;

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
	
}

void AMyPlayerController::BeginPlay()
{
	//PrintRole(Role);
	//ServerSpawnCharacter();
	//Test();
	if (Role == ROLE_Authority)
	{
		isServer = true;
	}
	else
	{
		isServer = false;
	}
	if (Role == ROLE_Authority)
		AddController();
	//ClientCheckMap(Role);
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, PlayerNum);
	DOREPLIFETIME(AMyPlayerController, MyGameState);
	DOREPLIFETIME(AMyPlayerController, ControllerPawn);
	DOREPLIFETIME(AMyPlayerController, MyName);
}

void AMyPlayerController::ServerSpawnCharacter()
{
	if (Role > ROLE_AutonomousProxy)
	{
		SpawnCharacter();
		}
}

void AMyPlayerController::InitCharacter()
{
	ServerSpawnCharacter();
	ControllerPawn = GetControlledPawn();
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(GetControlledPawn());
	//PrintCamp();
	MyCharacter->MyCamp = MyCamp;
	MyCharacter->RefreshLifeBar();
	MyCharacter->HeroProperty.LifeValue = MyCharacter->HeroProperty.MaxLifeValue;
	MyCharacter->ReBorn();
	//if (MyCharacter->MyCamp == ECamp::ERed)
	//{
	//	MyCharacter->SetActorLocation(RedLocation);
	//}
	//else if (MyCharacter->MyCamp == ECamp::EBlue)
	//{
	//	MyCharacter->SetActorLocation(BlueLocation);
	//}
}


void AMyPlayerController::BlueprintSpawnCharacter()
{
	ServerSpawnCharacter();
}

void AMyPlayerController::SetPosses_Implementation()
{
	if (Role == ROLE_AutonomousProxy)
	{
		counter++;
		PrintRole(Role, counter);
		//Possess(ControllerPawn);
		//SetViewTarget(GetControlledPawn());
	}
}

bool AMyPlayerController::SetPosses_Validate()
{
	return true;
}

void AMyPlayerController::PrintCamp_Implementation()
{

}
bool AMyPlayerController::PrintCamp_Validate()
{
	return true;
}

void AMyPlayerController::AddController()
{
	if (UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance()))
	{
		MyGameInstance->AddController(this);
	}
}

void AMyPlayerController::ClientCheckMap_Implementation(ENetRole thisRole)
{
	CheckMap(thisRole);
}
bool AMyPlayerController::ClientCheckMap_Validate(ENetRole thisRole)
{
	return true;
}

void AMyPlayerController::ServerSetName_Implementation(FName Name_)
{
	MyName = Name_;
}
bool AMyPlayerController::ServerSetName_Validate(FName Name_)
{
	return true;
}