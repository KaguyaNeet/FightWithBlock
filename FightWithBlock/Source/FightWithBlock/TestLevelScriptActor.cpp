// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "TestLevelScriptActor.h"
#include "BlockBase.h"
#include "MyStructs.h"

ATestLevelScriptActor::ATestLevelScriptActor()
{
	bReplicates = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> GroundTable(TEXT("DataTable'/Game/myBlueprint/DataTables/D_Ground.D_Ground'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> SurfaceTable(TEXT("DataTable'/Game/myBlueprint/DataTables/D_Surface.D_Surface'"));
	//ConstructorHelpers::FObjectFinder<UTexture2D> HeightMap(TEXT("Texture2D'/Game/WorldMachineOutput/output5.output5'"));
	//if (HeightMap.Succeeded())
	//{
	//	HeightFile = HeightMap.Object;
	//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("!!!!!!!!!!!!"));
	//}
	if (GroundTable.Succeeded() && SurfaceTable.Succeeded())
	{
		GroundDataTable = GroundTable.Object;
		SurfaceDataTable = SurfaceTable.Object;
		GroundRowNames = GroundTable.Object->GetRowNames();
		SurfaceRowNames = SurfaceTable.Object->GetRowNames();
	}
}

void ATestLevelScriptActor::TestPrintHeight(int32 x, int32 y)
{

	if (HeightFile)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("!!!!!!!!!!!!"));
		HeightFile->MipGenSettings.operator=(TMGS_NoMipmaps);
		HeightFile->SRGB = false;
		HeightFile->CompressionSettings.operator=(TC_VectorDisplacementmap);
		FTexture2DMipMap* MyMips = &HeightFile->PlatformData->Mips[0];
		//const FByteBulkData* RawImageData = &MyMips->BulkData;
		//auto FormatedImageData =  static_cast<FColor*>(RawImageData->Lock(LOCK_READ_ONLY));
		//MyMips->BulkData.Lock(LOCK_READ_ONLY);
		FColor* Color = static_cast<FColor*>(MyMips->BulkData.Lock(LOCK_READ_ONLY));
		//RawImageData->Lock(LOCK_READ_ONLY);
		FColor PixelColor;
		int32 Width = MyMips->SizeX;
		int32 Height = MyMips->SizeY;

		if (x >= 0 && x < Width && y >= 0 && y < Height)
		{
			//PixelColor = FormatedImageData[y * Width + x];
		}
		//UE_LOG(LogTemp, Warning, TEXT("Red:%d;Green:%d;Blue:%d"), PixelColor.R, PixelColor.G, PixelColor.B);
	}
}

void ATestLevelScriptActor::BeginPlay()
{
	if (Role == ROLE_Authority)
	{
		GenerateGround();
	}
	for (int i = 1; i < 10; i++)
	{
		TestPrintHeight(i, i);
	}
}

void ATestLevelScriptActor::GenerateGround()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Black, TEXT("GenerateGround_()!!!!!!!!!!"));
	if (MapSize > WarningSize)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("MapSize is too Big!!!!!!!!!!"));
		return;
	}
	else
	{
		FBlock* GroundRow = NULL;
		int32 x = 1, y = 1, z = 1;
		while (z <= MaxZ)
		{
			//GroundRowNames[(int)FMath::FRandRange(0.f, (float)(GroundRowNames.Num() - 1))];
			GroundRow = GroundDataTable->FindRow<FBlock>(GroundRowNames[(int)FMath::FRandRange(0.f, (float)(GroundRowNames.Num()))], TEXT(""));
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