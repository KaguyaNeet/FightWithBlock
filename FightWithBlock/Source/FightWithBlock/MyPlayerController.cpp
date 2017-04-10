// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "MyGameInstance.h"
#include "NET/UnrealNetwork.h"

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
}

void AMyPlayerController::BeginPlay()
{
	ServerSpawnCharacter();
	ControllerPawn = GetControlledPawn();
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, IsCampFull);
}

void AMyPlayerController::ServerSpawnCharacter_Implementation()
{
	if (Role > ROLE_AutonomousProxy)
	{
		SpawnCharacter();
		}
}
bool AMyPlayerController::ServerSpawnCharacter_Validate()
{
	return true;
}

void AMyPlayerController::SetCamp(ECamp Camp)
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(ControllerPawn);
	MyCharacter->MyCamp = Camp;
}

void AMyPlayerController::InitCharacter()
{
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(ControllerPawn);
	MyCharacter->RefreshLifeBar();
}

void AMyPlayerController::ChooseCamp(ECamp MyChoose)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		switch (MyChoose)
		{
		case ECamp::ERed: {
			if (Role < ROLE_Authority)
			{
				ServerChooseCamp(ECamp::ERed);
			}
			else
			{
				ServerChooseCamp_Implementation(ECamp::ERed);
			}
			break;
		}
		case ECamp::EBlue: {
			if (Role < ROLE_Authority)
			{
				ServerChooseCamp(ECamp::EBlue);
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
				SetCamp(MyChoose);
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
				SetCamp(MyChoose);
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