// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyCharacter.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	Camera->AttachTo(RootComponent);
	Camera->bUsePawnControlRotation = true;

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("myFPSMesh"));
	FPSMesh->AttachTo(Camera);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;
	FPSMesh->SetOnlyOwnerSee(true);

	GetMesh()->SetOwnerNoSee(true);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("this is MyCharacter!"));	
	}
	handBlock = Bag[0];

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnX", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnY", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Item_1", IE_Pressed, this, &AMyCharacter::chooseItem_1);
	PlayerInputComponent->BindAction("Item_2", IE_Pressed, this, &AMyCharacter::chooseItem_2);
	PlayerInputComponent->BindAction("Item_3", IE_Pressed, this, &AMyCharacter::chooseItem_3);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Fire);

}

void AMyCharacter::MoveForward(float val)
{
	AddMovementInput(GetActorForwardVector(), val * HeroInitProperty.MoveSpeed);
}

void AMyCharacter::MoveRight(float val)
{
	AddMovementInput(GetActorRightVector(), val * HeroInitProperty.MoveSpeed);
}

bool AMyCharacter::AddItem(FBlock Item)
{
	for (int i = 0; i < BAGSPACE; i++)
	{
		if (Bag[i].Empty)
		{
			Bag[i].Block = Item;
			Bag[i].Empty = false;
			return true;
		}
	}
	return false;
}


void AMyCharacter::chooseItem_1()
{
	handBlock = Bag[0];
}

void AMyCharacter::chooseItem_2()
{
	handBlock = Bag[1];
}

void AMyCharacter::chooseItem_3()
{
	handBlock = Bag[2];
}


FVector AMyCharacter::GetFireLocation()
{
	FVector tempLocation = FVector(0, 0, 0);
	return tempLocation;
}

FRotator AMyCharacter::GetFireRotation()
{
	FRotator tempRotation = FRotator(0, 0, 0);
	return tempRotation;
}

void AMyCharacter::Fire()
{
	if (handBlock.Empty == false)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			ABoltBlock* tempBlock = World->SpawnActor<ABoltBlock>(GetClass(), GetFireLocation(), GetFireRotation(), SpawnParams);
			tempBlock->SetInitProperty(handBlock.Block);
			tempBlock->SetFireDirection(GetActorRotation().Vector());
			handBlock.Empty = true;
		}
	}
}
