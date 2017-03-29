// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "TestCharcter.h"
#include "MyStructs.h"


// Sets default values
ATestCharcter::ATestCharcter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ConstructorHelpers::FObjectFinder<UTexture2D> HeightMap(TEXT(""));
	//if (HeightMap.Succeeded())
	//{
	//	HeightFile = HeightMap.Object;
	//}
}

// Called when the game starts or when spawned
void ATestCharcter::BeginPlay()
{
	Super::BeginPlay();
	
	//printHeight(1, 1);
}

void ATestCharcter::printHeight(int32 x, int32 y)
{
	if (HeightFile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("!!!!!!!!!!!!"));
		HeightFile->MipGenSettings.operator=(TMGS_NoMipmaps);
		HeightFile->SRGB = false;
		HeightFile->CompressionSettings.operator=(TC_VectorDisplacementmap);
		FTexture2DMipMap* MyMips = &HeightFile->PlatformData->Mips[0];
		FByteBulkData* RawImageData = &MyMips->BulkData;
		auto FormatedImageData = static_cast<FColor*>(RawImageData->Lock(LOCK_READ_ONLY));
		FColor PixelColor;
		int32 Width = MyMips->SizeX;
		int32 Height = MyMips->SizeY;

		if (x >= 0 && x < Width && y >= 0 && y < Height)
		{
			PixelColor = FormatedImageData[y * Width + x];
		}
		UE_LOG(LogTemp, Warning, TEXT("Red:%d;Green:%d;Blue:%d"), PixelColor.R, PixelColor.G, PixelColor.B);
	}
}

// Called every frame
void ATestCharcter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharcter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATestCharcter::Find);


}

void ATestCharcter::Find()
{
	ConstructorHelpers::FObjectFinder<UDataTable> TestTable(TEXT("DataTable'/Game/myBlueprint/DataTables/TestUse.TestUse'"));
	if (TestTable.Succeeded())
	{
		GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("Find TestUse"));
		UDataTable* TestUse = TestTable.Object;
		TArray<FName> RowNames = TestUse->GetRowNames();
		FHero* MyHero = TestUse->FindRow<FHero>(RowNames[0], TEXT(""));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MyHero->dName.ToString());
	}
}
