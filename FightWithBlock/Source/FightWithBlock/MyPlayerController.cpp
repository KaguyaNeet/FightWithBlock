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
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, IsCampFull);
	DOREPLIFETIME(AMyPlayerController, PlayerNum);
	DOREPLIFETIME(AMyPlayerController, MyGameState);
	DOREPLIFETIME(AMyPlayerController, ControllerPawn);
	DOREPLIFETIME(AMyPlayerController, MyCamp);
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

void AMyPlayerController::ChooseCamp(ECamp MyChoose)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		switch (MyChoose)
		{
		case ECamp::ERed: {
			//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("Red!!!!!!!!!!!!!"));
			if (Role < ROLE_Authority)
			{
				ServerChooseCamp(ECamp::ERed);
				MyCamp = ECamp::ERed;
			}
			else
			{
				ServerChooseCamp_Implementation(ECamp::ERed);
			}
			break;
		}
		case ECamp::EBlue: {
			//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("Blue!!!!!!!!!!!!!"));
			if (Role < ROLE_Authority)
			{
				ServerChooseCamp(ECamp::EBlue);
				MyCamp = ECamp::EBlue;
			}
			else
			{
				ServerChooseCamp_Implementation(ECamp::EBlue);
			}
			break;
		}
		}
	}
}

void AMyPlayerController::ServerChooseCamp_Implementation(ECamp MyChoose)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		switch (MyChoose)
		{
		case ECamp::ERed: {
			if (MyGameInstance->IsRedCampFull())
			{
				GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("FULL!!!!!!!!!!!!!"));
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("NOTFULL!!!!!!!!!!!!!"));
				MyGameInstance->RedCampAddController(this);
				IsCampFull = false;
				IsChooseCamp = true;
				MyCamp = MyChoose;
				//SetCamp(MyChoose);
			}
			break;
		}
		case ECamp::EBlue: {
			//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Black, TEXT("NOTBreak!!!!!!!!!!!!!"));
			if (MyGameInstance->IsBlueCampFull())
			{
			}
			else
			{
				MyGameInstance->BlueCampAddController(this);
				IsCampFull = false;
				IsChooseCamp = true;
				MyCamp = MyChoose;
				//SetCamp(MyChoose);
			}
			break;
		}
		}
	}
}
bool AMyPlayerController::ServerChooseCamp_Validate(ECamp MyChoose)
{
	return true;
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