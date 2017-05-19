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

void AMyPlayerController::ServerSetzhanlan_Implementation()
{
	Setzhanlan();
}
bool AMyPlayerController::ServerSetzhanlan_Validate()
{
	return true;
}

void AMyPlayerController::ServerControllerReady_Implementation()
{
	if (Role >= ROLE_AutonomousProxy)
		ControllerReady();
}
bool AMyPlayerController::ServerControllerReady_Validate()
{
	return true;
}

void AMyPlayerController::PlayerReady()
{
	isDeath = false;
	ServerSpawnCharacter();
	//ClientSetName();
	ClientEndText();
	ClientAddStartMessage();
	ServerSetAllowInput(false);
}
void AMyPlayerController::PlayerStart()
{
	ServerSetAllowInput(true);
}

void AMyPlayerController::ClientEndText_Implementation()
{
	if (Role >= ROLE_AutonomousProxy)
		EndText();
}
bool AMyPlayerController::ClientEndText_Validate()
{
	return true;
}

void AMyPlayerController::ServerCharacterDeath_Implementation()
{
	if (Role == ROLE_Authority)
	{
		CharacterDeath();
	}
}
bool AMyPlayerController::ServerCharacterDeath_Validate()
{
	return true;
}

void AMyPlayerController::CharacterDeath()
{
	if (UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance()))
	{
		MyGameInstance->ApplyKill(MyName, this);
		isDeath = true;
	}
}

void AMyPlayerController::ClientPrintKillMessage_Implementation(FName Name)
{
	if (Role >= ROLE_AutonomousProxy)
	{
		PrintKillMessage(Name);
	}
}
bool AMyPlayerController::ClientPrintKillMessage_Validate(FName Name)
{
	return true;
}

void AMyPlayerController::ClientTargetMoveToWinner_Implementation(AMyPlayerController* Controller)
{
	if (Role >= ROLE_AutonomousProxy)
	{
		TargetMoveToWinner(Controller);
	}
}
bool AMyPlayerController::ClientTargetMoveToWinner_Validate(AMyPlayerController* Controller)
{
	return true;
}

void AMyPlayerController::ServerSetAllowInput_Implementation(bool Choose)
{
	if (Role >= ROLE_AutonomousProxy)
		SetAllowInput(Choose);
}
bool AMyPlayerController::ServerSetAllowInput_Validate(bool Choose)
{
	return true;
}

void AMyPlayerController::ClientAddStartMessage_Implementation()
{
	if (Role >= ROLE_AutonomousProxy)
	{
		AddStartMessage();
	}
}
bool AMyPlayerController::ClientAddStartMessage_Validate()
{
	return true;
}

//void AMyPlayerController::ClientSetName_Implementation()
//{
//	if (Role >= ROLE_AutonomousProxy)
//	{
//		if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(GetControlledPawn()))
//		{
//			MyCharacter->HeroName = MyName;
//		}
//	}
//}
//bool AMyPlayerController::ClientSetName_Validate()
//{
//	return true;
//}