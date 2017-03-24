// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "TestLevelScriptActor.h"
#include "BlockBase.h"
#include "MyStructs.h"
//#include "Runtime/UMG/Public/UMG.h"
//#include "Runtime/UMG/Public/UMGStyle.h"
//#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
//#include "Runtime/UMG/Public/IUMGModule.h"

ATestLevelScriptActor::ATestLevelScriptActor()
{
	bReplicates = true;
	ConstructorHelpers::FObjectFinder<UTexture2D> HeightTexture(TEXT("Texture2D'/Game/WorldMachineOutput/test1.test1'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> GroundTable(TEXT("DataTable'/Game/myBlueprint/DataTables/D_Ground.D_Ground'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> SurfaceTable(TEXT("DataTable'/Game/myBlueprint/DataTables/D_Surface.D_Surface'"));
	//ConstructorHelpers::FObjectFinder<UUserWidget> SessionRoom(TEXT("WidgetBlueprint'/Game/UMG/SessionRoom.SessionRoom'"));
	if (GroundTable.Succeeded() && SurfaceTable.Succeeded())
	{
		GroundDataTable = GroundTable.Object;
		SurfaceDataTable = SurfaceTable.Object;
		GroundRowNames = GroundTable.Object->GetRowNames();
		SurfaceRowNames = SurfaceTable.Object->GetRowNames();
	}
	if (HeightTexture.Succeeded())
	{
		Map = HeightTexture.Object;
	}
}

void ATestLevelScriptActor::BeginPlay()
{
	if (Role == ROLE_Authority)
	{
		GenerateGround();
	}
}

void ATestLevelScriptActor::GenerateGround()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, TEXT("GenerateGround_()!!!!!!!!!!"));
	if (MapSize > WarningSize)
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
			//GroundRowNames[(int)FMath::FRandRange(0.f, (float)(GroundRowNames.Num() - 1))];
			GroundRow = GroundDataTable->FindRow<FBlock>(GroundRowNames[(int)FMath::FRandRange(0.f, (float)(GroundRowNames.Num() - 1))], TEXT(""));
			GroundRow->Position.X = x; GroundRow->Position.Y = y; GroundRow->Position.Z = z;
			AllBlockInfo.Add(SpawnBlock(GroundRow, BlockSize * DSize));
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


ABlockBase* ATestLevelScriptActor::SpawnBlock(const FBlock* Block, float Size)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Spawn!!!!!!!!!!"));
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