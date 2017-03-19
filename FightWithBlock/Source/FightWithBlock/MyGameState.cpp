// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyGameState.h"
#include "BlockBase.h"
#include "MyStructs.h"



AMyGameState::AMyGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> GroundTable(TEXT("DataTable'/Game/myBlueprint/DataTables/D_Ground.D_Ground'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> SurfaceTable(TEXT("DataTable'/Game/myBlueprint/DataTables/D_Surface.D_Surface'"));
	if (GroundTable.Succeeded() && SurfaceTable.Succeeded())
	{
		GroundDataTable = GroundTable.Object;
		SurfaceDataTable = SurfaceTable.Object;
		GroundRowNames = GroundTable.Object->GetRowNames();
		SurfaceRowNames = SurfaceTable.Object->GetRowNames();
	}
}

void AMyGameState::BeginPlay()
{
	/*GenerateGround();
	if(Role == ROLE_Authority)
		GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("ROLE_Authority!!!!!!!!!!"));
	if(Role == ROLE_AutonomousProxy)
		GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("ROLE_AutonomousProxy!!!!!!!!!!"));
	if(Role == ROLE_SimulatedProxy)
		GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("ROLE_SimulatedProxy!!!!!!!!!!"));*/
}

void AMyGameState::GenerateGround_()
{
	if (MapSize > 100)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("MapSize is too Big!!!!!!!!!!"));
		return;
	}
	else
	{
		FBlock* GroundRow = NULL;
		int32 x = 1, y = 1, z = 1;
		while (z <= MaxZ)
		{
			GroundRowNames[(float)FMath::FRandRange(0.f, (float)(GroundRowNames.Num() - 1))];
			GroundRow = GroundDataTable->FindRow<FBlock>(GroundRowNames[(float)FMath::FRandRange(0.f, (float)(GroundRowNames.Num() - 1))], TEXT(""));
			GroundRow->Position.X = x; GroundRow->Position.Y = y; GroundRow->Position.Z = z;
			AllBlockInfo.Add(SpawnBlock(GroundRow, BlockSize));
			x += 1;
			if (x > MapSize)
			{
				x = 1;
				y += 1;
				if (y > MapSize)
				{
					y = 1;
					z += 1;
				}
			}
		}
		return;
	}
}
void AMyGameState::GenerateGround()
{
	if (Role < ROLE_Authority)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Green, TEXT("Client!!!!!!!!!!!!!!!!"));
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("Server!!!!!!!!!!!!!!!!"));
		ServerGenerateGround();
	}
}
void AMyGameState::ServerGenerateGround_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("Spawn!!!!!!!!!!!!!!!!"));
	GenerateGround_();
}
bool AMyGameState::ServerGenerateGround_Validate()
{
	return true;
}

ABlockBase* AMyGameState::SpawnBlock(const FBlock* Block, float Size)
{
	//GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("Spawn!!!!!!!!!!!!!!!!"));
	FVector location = FVector(Block->Position.X * Size, Block->Position.Y * Size, Block->Position.Z * Size);
	UWorld* World = GetWorld();
	ABlockBase* tempBlock = NULL;
	if (World)
	{
		tempBlock = World->SpawnActor<ABlockBase>(location, FRotator(0, 0, 0));
		tempBlock->SetInitProperty(*Block);
		return tempBlock;
	}
	else
	{
		return tempBlock;
	}
}