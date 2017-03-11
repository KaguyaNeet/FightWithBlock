// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "FightWithBlockGameModeBase.h"
#include "BlockBase.h"
#include "MyStructs.h"


void AFightWithBlockGameModeBase::PrintKillMessage(class AMyCharacter* Killer, class AMyCharacter* beKiller)
{

}

void AFightWithBlockGameModeBase::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("GameModeCPP"));
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		ABlockBase* temp;
		temp = World->SpawnActor<ABlockBase>(FVector(0,0,0), FRotator(0,0,0), SpawnParams);
		FBlock MyBlock;
		temp->SetInitProperty(MyBlock);
	}
}

