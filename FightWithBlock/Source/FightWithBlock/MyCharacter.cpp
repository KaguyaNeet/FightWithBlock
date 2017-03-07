// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyCharacter.h"
#include "BlockBase.h"


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

	GetCapsuleComponent()->OnComponentBeginOverlap.__Internal_AddDynamic(this, &AMyCharacter::BeginOverlap, TEXT("BeginOverlap"));
	GetMesh()->SetOwnerNoSee(true);

	MineTraceStartArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("MineTraceStartArrow"));

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

	RunBUFF(DeltaTime);

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
	PlayerInputComponent->BindAction("GetItem", IE_Pressed, this, &AMyCharacter::Pressed_R);
	PlayerInputComponent->BindAction("GetItem", IE_Released, this, &AMyCharacter::Released_R);

}

void AMyCharacter::MoveForward(float val)
{
	AddMovementInput(GetActorForwardVector(), val * 10);
}

void AMyCharacter::MoveRight(float val)
{
	AddMovementInput(GetActorRightVector(), val * 10);
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
	if (!handBlock.Empty)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			ABoltBlock* tempBlock = World->SpawnActor<ABoltBlock>(GetClass(), GetFireLocation(), GetFireRotation(), SpawnParams);
			tempBlock->SetInitProperty(handBlock.Block, this);
			tempBlock->SetFireDirection(GetActorRotation().Vector());
			handBlock.Empty = true;
		}
	}
}

void AMyCharacter::ReloadProperty()
{
	MovementComponent->MaxWalkSpeed = HeroProperty.MoveSpeed;
}


void AMyCharacter::AddBUFF(FBUFF BUFF)
{
		myBUFF.Add(BUFF);
}

void AMyCharacter::RunBUFF(float DeltaTime)
{
	for (int i = 0; i < myBUFF.Max(); i++)
	{
		if (i == myBUFF.Max())
			break;
		else
		{
			if (myBUFF[i].LifeTime <= 0)
			{
				EndBUFF(i);
			}
			myBUFF[i].LifeTime -= DeltaTime;
			if (myBUFF[i].xuanyun)
			{
				MovementComponent->MaxWalkSpeed = 0;
			}
			if (!myBUFF[i].alreadyChangeSpeed)
				MovementComponent->MaxWalkSpeed *= myBUFF[i].changeSpeed;
			HeroProperty.LifeValue += myBUFF[i].changeHP * DeltaTime;
			HeroProperty.Power += myBUFF[i].changePower * DeltaTime;
		}
	}
}

void AMyCharacter::EndBUFF(int i)
{
	myBUFF.RemoveAt(i);
	ReloadProperty();
}

void AMyCharacter::BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
{
	ACBGBlock* CBGBlock = Cast<ACBGBlock>(OtherActor);
	if (CBGBlock)
	{
		if (Keyboard_F_Pressed)
		{
			if (AddItem(CBGBlock->BlockProperty))
			{
				CBGBlock->DestroySelf();
			}
		}
	}
}

void AMyCharacter::Pressed_R()
{
	Keyboard_F_Pressed = true;
}

void AMyCharacter::Released_R()
{
	Keyboard_F_Pressed = false;
}

void AMyCharacter::PrintItem(FBlock BlockProperty)
{

}

void AMyCharacter::MineBlock(float DeltaTime)
{
	MineTimeCounter += DeltaTime;
	if (MineTimeCounter >= HeroProperty.MineRate)
	{
		MineTimeCounter = 0;
		UWorld* World = GetWorld();
		if (World)
		{
			FHitResult TraceHit;
			if (World->LineTraceSingleByChannel(TraceHit, MineTraceStartArrow->GetComponentLocation(), MineTraceStartArrow->GetComponentLocation() + MineTraceStartArrow->GetForwardVector() * HeroProperty.MineDistance, ECollisionChannel::ECC_WorldStatic))
			{
				MineLineTraceResult(TraceHit);
			}
		}
	}
	else
		return;
}

void AMyCharacter::MineLineTraceResult(const FHitResult& Hit)
{
	ABlockBase* HitBlock = Cast<ABlockBase>(Hit.GetActor());
	if (HitBlock)
	{
		HitBlock->ApplyPointDamage(this, HeroProperty.BlockDamage);
	}
}

void AMyCharacter::ApplyPointDamage(AMyCharacter* Causer, int32 DmageValue)
{

}