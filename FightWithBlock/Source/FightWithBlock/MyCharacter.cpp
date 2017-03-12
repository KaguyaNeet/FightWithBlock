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


	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::BeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::EndOverlap);
	GetMesh()->SetOwnerNoSee(true);

	MineTraceStartArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("MineTraceStartArrow"));
	MineTraceStartArrow->AttachTo(Camera);
	MineTraceStartArrow->SetRelativeLocation(FVector(0, 0, 0));
	MineTraceStartArrow->SetHiddenInGame(true);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	//测试用要删的！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	//多打几行引起注意！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	HeroProperty.LifeValue = 1;
	HeroProperty.BlockDamage = 1;
	HeroProperty.MineRate = 0.2;
	HeroProperty.MineDistance = 200;
	//ConstructorHelpers::FObjectFinder<UDataTable> TestTable(TEXT("DataTable'/Game/myBlueprint/DataTables/TestUse.TestUse'"));
	//if (TestTable.Succeeded())
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("Find TestUse"));
	//	UDataTable* TestUse = TestTable.Object;
	//	TArray<FName> RowNames = TestUse->GetRowNames();
	//	FHero* MyHero = TestUse->FindRow<FHero>(RowNames[0], TEXT(""));
	//	UE_LOG(LogTemp, Warning, TEXT("%s"), *MyHero->dName.ToString());
	//}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("this is MyCharacter!"));	
	}
	handBlock = &Bag[0];
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunBUFF(DeltaTime);
	MineTimeCounter += DeltaTime;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("%f"), HeroProperty.MineDistance);
	//UE_LOG(LogTemp, Warning, TEXT("DISTANCE:%f"), HeroProperty.MineDistance);
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
	PlayerInputComponent->BindAction("MineBlock", IE_Pressed, this, &AMyCharacter::MineBlock);

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
			AddBUFF(Item.ToOwnerBUFF);
			return true;
		}
	}
	if (!handBlock->Empty)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("FULL!!!"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			ACBGBlock* tempBlock = World->SpawnActor<ACBGBlock>(Camera->GetComponentLocation(), GetActorRotation(), SpawnParams);
			tempBlock->SetInitProperty(handBlock->Block);
			handBlock->Block = Item;
			handBlock->Empty = false;
			AddBUFF(Item.ToOwnerBUFF);
			return true;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("Warning!!!"));
	return false;
}


void AMyCharacter::chooseItem_1()
{
	handBlock = &Bag[0];
}

void AMyCharacter::chooseItem_2()
{
	handBlock = &Bag[1];
}

void AMyCharacter::chooseItem_3()
{
	handBlock = &Bag[2];
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
	if (!handBlock->Empty)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(MineTraceStartArrow->GetComponentLocation()).ToString());
			ABoltBlock* tempBlock = World->SpawnActor<ABoltBlock>(MineTraceStartArrow->GetComponentLocation(), GetFireRotation());
			tempBlock->SetInitProperty(handBlock->Block, this);
			tempBlock->SetFireDirection(MineTraceStartArrow->GetForwardVector(), 1000);
			handBlock->Empty = true;
		}
	}
}

void AMyCharacter::ReloadProperty()
{
	//MovementComponent->MaxWalkSpeed = 300.f;
	//HeroProperty.MoveSpeed
}


void AMyCharacter::AddBUFF(FBUFF BUFF)
{
		myBUFF.Add(BUFF);
}

void AMyCharacter::RunBUFF(float DeltaTime)
{
	for (int i = 0; i < myBUFF.Num(); i++)
	{
		if (i == myBUFF.Num())
			break;
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), myBUFF.Num())
			if (myBUFF[i].LifeTime <= 0)
			{
				EndBUFF(i);
				return;
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
			UGameplayStatics::SpawnEmitterAttached(myBUFF[i].Particle, GetMesh());
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Overlap!"));
	ACBGBlock* CBGBlock = Cast<ACBGBlock>(OtherActor);
	if (CBGBlock)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Find!"));
		AddBlockToPre(CBGBlock);
	}
}

void AMyCharacter::EndOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("EndOverlap!"));
	ACBGBlock* CBGBlock = Cast<ACBGBlock>(OtherActor);
	if (CBGBlock)
	{
		RemoveBlockFromPre(CBGBlock);
	}
}

void AMyCharacter::AddBlockToPre(ACBGBlock* Block)
{
	for (int i = 0; i < 3; i++)
	{
		if (printBlock[i] == NULL)
		{
			printBlock[i] = Block;
			break;
		}
	}
}

void AMyCharacter::RemoveBlockFromPre(ACBGBlock* Block)
{
	for (int i = 0; i < 3; i++)
	{
		if (printBlock[i] == Block)
		{
			printBlock[i] = NULL;
			break;
		}
	}
}

void AMyCharacter::Pressed_R()
{
	for (int i = 0; i < 3; i++)
	{
		if (printBlock[i] != NULL)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("PreGET!"));
			if (AddItem(printBlock[i]->BlockProperty))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("GET!"));
				printBlock[i]->DestroySelf();
				printBlock[i] = NULL;
				break;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GETFalse!"));
				printBlock[i] = NULL;
			}
		}
	}
}

void AMyCharacter::Released_R()
{
	Keyboard_F_Pressed = false;
}

void AMyCharacter::PrintItem(FBlock BlockProperty)
{

}

void AMyCharacter::MineBlock()
{
	if (MineTimeCounter >= HeroProperty.MineRate)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mine"));
		MineTimeCounter = 0;
		UWorld* World = GetWorld();
		if (World)
		{
			FHitResult TraceHit;
			//UE_LOG(LogTemp, Warning, TEXT("起始点：%s"), *(MineTraceStartArrow->GetComponentLocation()).ToString());
			//UE_LOG(LogTemp, Warning, TEXT("末尾点：%s"), *(MineTraceStartArrow->GetComponentLocation() + MineTraceStartArrow->GetForwardVector() * HeroProperty.MineDistance).ToString());
			//UE_LOG(LogTemp, Warning, TEXT("距离：%f"), ((MineTraceStartArrow->GetForwardVector() * HeroProperty.MineDistance) - (MineTraceStartArrow->GetComponentLocation())).Size());
			if (World->LineTraceSingleByChannel(TraceHit, MineTraceStartArrow->GetComponentLocation(), MineTraceStartArrow->GetComponentLocation() + MineTraceStartArrow->GetForwardVector() * HeroProperty.MineDistance, ECollisionChannel::ECC_Visibility))
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MineHit"));
		HitBlock->ApplyPointDamage(this, HeroProperty.BlockDamage);
	}
}

void AMyCharacter::ApplyPointDamage(AMyCharacter* Causer, int32 DamageValue)
{
	HeroProperty.LifeValue -= DamageValue;
	if (HeroProperty.LifeValue <= 0)
	{
		Death(Causer);
	}
}

void AMyCharacter::Death(AMyCharacter* Causer)
{
	if (GetWorld())
		GetWorld()->GetAuthGameMode<AFightWithBlockGameModeBase>()->PrintKillMessage(Causer, this);
	this->Destroy(true);
	return;
}
