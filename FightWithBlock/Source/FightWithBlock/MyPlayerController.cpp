// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "MyGameInstance.h"


AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
}

void AMyPlayerController::BeginPlay()
{
	SpawnCharacter();
}

void AMyPlayerController::SpawnCharacter_Implementation()
{
	UWorld* World = GetWorld();
	if (World)
	{
		ControllerPawn = World->SpawnActor<AMyCharacter>(RedLocation, FRotator(0, 0, 0));
		Possess(ControllerPawn);
	}
}
bool AMyPlayerController::SpawnCharacter_Validate()
{
	return true;
}

void AMyPlayerController::SetCamp(ECamp Camp)
{

}