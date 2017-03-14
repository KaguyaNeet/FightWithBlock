// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "TestCharcter.h"
#include "MyStructs.h"


// Sets default values
ATestCharcter::ATestCharcter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestCharcter::BeginPlay()
{
	Super::BeginPlay();
	
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
