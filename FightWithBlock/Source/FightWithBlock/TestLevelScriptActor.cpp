// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "TestLevelScriptActor.h"
#include "BlockBase.h"
#include "MyStructs.h"
#include "MyGameInstance.h"

ATestLevelScriptActor::ATestLevelScriptActor()
{
	bReplicates = true;
	static ConstructorHelpers::FObjectFinder<UDataTable> GroundTable(TEXT("DataTable'/Game/myBlueprint/DataTables/D_Ground.D_Ground'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> SurfaceTable(TEXT("DataTable'/Game/myBlueprint/DataTables/D_Surface.D_Surface'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> WallTable(TEXT("DataTable'/Game/myBlueprint/DataTables/D_Wall.D_Wall'"));
	//ConstructorHelpers::FObjectFinder<UTexture2D> HeightMap(TEXT("Texture2D'/Game/WorldMachineOutput/output5.output5'"));
	//if (HeightMap.Succeeded())
	//{
	//	HeightFile = HeightMap.Object;
	//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("!!!!!!!!!!!!"));
	//}
	if (WallTable.Succeeded())
	{
		WallDataTable = WallTable.Object;
		WallRowNames = WallTable.Object->GetRowNames();
	}
	if (GroundTable.Succeeded() && SurfaceTable.Succeeded())
	{
		GroundDataTable = GroundTable.Object;
		SurfaceDataTable = SurfaceTable.Object;
		GroundRowNames = GroundTable.Object->GetRowNames();
		SurfaceRowNames = SurfaceTable.Object->GetRowNames();
	}
}

void ATestLevelScriptActor::BeginPlay()
{
	StartInit();
	CheckReady();
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
		FBlock GroundRow;
		int32 x = 1, y = 1, z = 1;
		while (z <= MaxZ)
		{
			//GroundRowNames[(int)FMath::FRandRange(0.f, (float)(GroundRowNames.Num() - 1))];
			GroundRow = *GroundDataTable->FindRow<FBlock>(GroundRowNames[(int)FMath::FRandRange(0.f, (float)(GroundRowNames.Num()))], TEXT(""));
			GroundRow.Position.X = x; GroundRow.Position.Y = y; GroundRow.Position.Z = z;
			GroundRow.Size *= DSize;
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


ABlockBase* ATestLevelScriptActor::SpawnBlock(const FBlock Block, float Size)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Spawn!!!!!!!!!!"));
	FVector location = FVector(Block.Position.X * Size, Block.Position.Y * Size, Block.Position.Z * Size);
	UWorld* World = GetWorld();
	ABlockBase* tempBlock = NULL;
	if (World)
	{
		tempBlock = World->SpawnActor<ABlockBase>(location, FRotator(0, 0, 0));
		tempBlock->SetInitProperty(Block);
		return tempBlock;
	}
	else
	{
		return tempBlock;
	}
}

void ATestLevelScriptActor::GenerateGroundWall()
{
	int32 x = 1, y = 1, z = 0;
	FBlock WallRow;
	UWorld* World = GetWorld();
	ABlockBase* Wall = NULL;
	WallRow = *WallDataTable->FindRow<FBlock>(WallRowNames[0], TEXT(""));
	WallRow.Size *= DSize;
	if (World)
	{
		while (z == 0)
		{
			//WallRow.Position.X = x; WallRow.Position.Y = y; WallRow.Position.Z = z;
			FVector Location = FVector(x*BlockSize, y*BlockSize, z*BlockSize);
			Wall = World->SpawnActor<ABlockBase>(Location, FRotator(0, 0, 0));
			Wall->SetInitProperty(WallRow);
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
	}
}

void ATestLevelScriptActor::GenerateWall()
{
	int z = 0;
	FBlock WallRow;
	UWorld* World = GetWorld();
	ABlockBase* Wall = NULL;
	WallRow = *WallDataTable->FindRow<FBlock>(WallRowNames[0], TEXT(""));
	WallRow.Size *= DSize;
	if (World)
	{
		while (z <= 12)
		{
			GenerateWall_x(z, WallRow);
			GenerateWall_y(z, WallRow);
			GenerateWall_Corner(z, WallRow);
			z++;
		}
	}
}

void ATestLevelScriptActor::GenerateWall_x(int z, FBlock Block)
{
	int32 x = 1;
	UWorld* World = GetWorld();
	ABlockBase* Wall = NULL;
	if (World)
	{
		while (x <= MapSize)
		{
			if (FMath::FRand() < ((float)z - 4.f) / 7.f)
			{
				if (1 <= WallRowNames.Num())
				Block.Material = WallDataTable->FindRow<FBlock>(WallRowNames[1], TEXT(""))->Material;
			}
			else
			{
				Block.Material = WallDataTable->FindRow<FBlock>(WallRowNames[0], TEXT(""))->Material;
			}
			FVector Location1 = FVector(x*BlockSize, 0*BlockSize, z*BlockSize);
			FVector Location2 = FVector(x*BlockSize, (MapSize + 1)*BlockSize, z*BlockSize);
			Wall = World->SpawnActor<ABlockBase>(Location1, FRotator(0, 0, 0));
			Wall->SetInitProperty(Block);
			Wall = World->SpawnActor<ABlockBase>(Location2, FRotator(0, 0, 0));
			Wall->SetInitProperty(Block);
			x++;
		}
	}
}
void ATestLevelScriptActor::GenerateWall_y(int z, FBlock Block)
{
	int32 y = 1;
	UWorld* World = GetWorld();
	ABlockBase* Wall = NULL;
	if (World)
	{
		while (y <= MapSize)
		{
			if (FMath::FRand() < ((float)z - 4.f) / 7.f)
			{
				if (1 <= WallRowNames.Num())
					Block.Material = WallDataTable->FindRow<FBlock>(WallRowNames[1], TEXT(""))->Material;
			}
			else
			{
				Block.Material = WallDataTable->FindRow<FBlock>(WallRowNames[0], TEXT(""))->Material;
			}
			FVector Location1 = FVector(0 * BlockSize, y * BlockSize, z*BlockSize);
			FVector Location2 = FVector((MapSize + 1)*BlockSize, y *BlockSize, z*BlockSize);
			Wall = World->SpawnActor<ABlockBase>(Location1, FRotator(0, 0, 0));
			Wall->SetInitProperty(Block);
			Wall = World->SpawnActor<ABlockBase>(Location2, FRotator(0, 0, 0));
			Wall->SetInitProperty(Block);
			y++;
		}
	}
}
void ATestLevelScriptActor::GenerateWall_Corner(int z, FBlock Block)
{
	UWorld* World = GetWorld();
	ABlockBase* Wall = NULL;
	if (World)
	{
		if (FMath::FRand() < ((float)z - 4.f) / 7.f)
		{
			if (1 <= WallRowNames.Num())
				Block.Material = WallDataTable->FindRow<FBlock>(WallRowNames[1], TEXT(""))->Material;
		}
		else
		{
			Block.Material = WallDataTable->FindRow<FBlock>(WallRowNames[0], TEXT(""))->Material;
		}
			FVector Location1 = FVector(0 * BlockSize, 0 * BlockSize, z*BlockSize);
			FVector Location2 = FVector(0*BlockSize, (MapSize + 1) *BlockSize, z*BlockSize);
			FVector Location3 = FVector((MapSize + 1)*BlockSize, 0 *BlockSize, z*BlockSize);
			FVector Location4 = FVector((MapSize + 1)*BlockSize, (MapSize + 1) *BlockSize, z*BlockSize);
			Wall = World->SpawnActor<ABlockBase>(Location1, FRotator(0, 0, 0));
			Wall->SetInitProperty(Block);
			Wall = World->SpawnActor<ABlockBase>(Location2, FRotator(0, 0, 0));
			Wall->SetInitProperty(Block);
			Wall = World->SpawnActor<ABlockBase>(Location3, FRotator(0, 0, 0));
			Wall->SetInitProperty(Block);
			Wall = World->SpawnActor<ABlockBase>(Location4, FRotator(0, 0, 0));
			Wall->SetInitProperty(Block);
	}
}

void ATestLevelScriptActor::ReadHeightMap()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("!!!!!!!!!"));

	FILE *fp;

	unsigned short bfType = 0; //the type of file, must be BM
	int64 bfOffBits = 0;       //the position of data
	int64 BmpWidth = 0;          // width of bmp
	int64 BmpHeight = 0;         //height of bmp
	fopen_s(&fp, "outputx.bmp", "r+");
	if (fp == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Cannot open HightMap.bmp...pyx.txt"));
		return;
	}
	//set read point to file begin Texture2D'/Game/StarterContent/Textures/T_Burst_M.T_Burst_M'
	fseek(fp, 0L, SEEK_SET);
	fread(&bfType, sizeof(char), 2, fp); //read type. 19778 is bmp
	if (bfType != 19778)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("Not bmp"));
		fclose(fp);
		return;
	}

	//find out date position
	fseek(fp, 10L, SEEK_SET);
	fread(&bfOffBits, sizeof(char), 4, fp);

	//get width and height of bmp
	fseek(fp, 18L, SEEK_SET);
	fread(&BmpWidth, sizeof(char), 4, fp);
	fread(&BmpHeight, sizeof(char), 4, fp);

	//get data
	fseek(fp, bfOffBits, SEEK_SET);
	BYTE *pBuf = new BYTE[BmpWidth*BmpHeight];
	fread(pBuf, sizeof(char), BmpWidth*BmpHeight, fp);
	fclose(fp);

	UWorld* World = GetWorld();
	ABlockBase* temp =NULL;
	//sapwn Block
	FBlock tmpBlock;
	int i = FMath::RandRange(0, (int)(BmpWidth - MapSize - 1));
	int j = FMath::RandRange(0, (int)(BmpWidth - MapSize - 1));
	int x, y, z;
	for (x = 1; x <= MapSize; x++, i++)
		for (y = 1; y <= MapSize; y++, j++)
		{
			for (z = 1; z <= pBuf[(i*BmpHeight + j)]; z++)
			{
				tmpBlock = *GroundDataTable->FindRow<FBlock>(GroundRowNames[(float)FMath::FRandRange(0.f, (float)(GroundRowNames.Num()))], TEXT(""));
				tmpBlock.Size *= DSize;
				FVector Location = FVector(x * BlockSize, y * BlockSize, z * BlockSize);
				temp = World->SpawnActor<ABlockBase>(Location, FRotator(0, 0, 0));
				//if (temp)
				//{
				//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("HAHAHAHA"));
				//}
				temp->SetInitProperty(tmpBlock);
			}
		}

	//AllBlockInfo.Add(SpawnBlock(tmpBlock, BlockSize));
}

void ATestLevelScriptActor::CreateMap()
{
	if (Role == ROLE_Authority)
	{
		ReadHeightMap();
		//MulticastAddLoadingUI();
		//GenerateGround();
		GenerateGroundWall();
		GenerateWall();
	}
}

void ATestLevelScriptActor::GameStart()
{
	if (Role == ROLE_Authority)
	{
		
		if (UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance()))
		{
			//MyGameInstance->GameStart();
		}
	}
}