// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "HerosBase.h"
#include "BlockBase.h"

// Sets default values
AHerosBase::AHerosBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bReplicateMovement = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	Camera->AttachTo(RootComponent);
	Camera->bUsePawnControlRotation = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> FPSSkeletalMesh(TEXT("SkeletalMesh'/Game/FirstPerson/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'"));
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("myFPSMesh"));
	FPSMesh->SetSkeletalMesh(FPSSkeletalMesh.Object);
	FPSMesh->SetRelativeLocation(FVector(0, 0, -170));
	FPSMesh->SetRelativeRotation(FRotator(0, -90, 0));
	FPSMesh->AttachTo(Camera);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;
	FPSMesh->SetOnlyOwnerSee(true);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TPSSkeletalMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	//ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBlueprint(TEXT("AnimBlueprint'/Game/myBlueprint/PlayerAnimBP.PlayerAnimBP'"));
	GetMesh()->SetSkeletalMesh(TPSSkeletalMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	/*if (AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBlueprint.Object->GeneratedClass);
	}*/

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	//GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AHerosBase::BeginOverlap);
	//GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AHerosBase::EndOverlap);


	MineTraceStartArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("MineTraceStartArrow"));
	MineTraceStartArrow->AttachTo(Camera);
	MineTraceStartArrow->SetRelativeLocation(FVector(0, 0, 0));
	MineTraceStartArrow->SetHiddenInGame(true);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	//测试用要删的！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	//多打几行引起注意！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	//HeroProperty.LifeValue = 1;
	//HeroProperty.BlockDamage = 1;
	//HeroProperty.MineRate = 0.2;
	//HeroProperty.MineDistance = 200;
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
void AHerosBase::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("this is MyHeros!"));
	}
	//handBlock = &Bag[0];
}

// Called every frame
void AHerosBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//RunBUFF(DeltaTime);
	//MineTimeCounter += DeltaTime;
}

// Called to bind functionality to input
void AHerosBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHerosBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHerosBase::MoveRight);
	PlayerInputComponent->BindAxis("TurnX", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnY", this, &APawn::AddControllerPitchInput);

	//PlayerInputComponent->BindAction("Item_1", IE_Pressed, this, &AHerosBase::chooseItem_1);
	//PlayerInputComponent->BindAction("Item_2", IE_Pressed, this, &AHerosBase::chooseItem_2);
	//PlayerInputComponent->BindAction("Item_3", IE_Pressed, this, &AHerosBase::chooseItem_3);
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHerosBase::Fire);
	//PlayerInputComponent->BindAction("GetItem", IE_Pressed, this, &AHerosBase::Pressed_R);
	//PlayerInputComponent->BindAction("GetItem", IE_Released, this, &AHerosBase::Released_R);
	//PlayerInputComponent->BindAction("MineBlock", IE_Pressed, this, &AHerosBase::MineBlock);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHerosBase::Jump);
}

void AHerosBase::MoveForward(float val)
{
	AddMovementInput(GetActorForwardVector(), val * 10);
}

void AHerosBase::MoveRight(float val)
{
	AddMovementInput(GetActorRightVector(), val * 10);
}

//bool AHerosBase::AddItem(FBlock Item)
//{
//	for (int i = 0; i < BAGSPACE; i++)
//	{
//		if (Bag[i].Empty)
//		{
//			Bag[i].Block = Item;
//			Bag[i].Empty = false;
//			AddBUFF(Item.ToOwnerBUFF);
//			return true;
//		}
//	}
//	if (!handBlock->Empty)
//	{
//		UWorld* World = GetWorld();
//		if (World)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("FULL!!!"));
//			FActorSpawnParameters SpawnParams;
//			SpawnParams.Owner = this;
//			SpawnParams.Instigator = Instigator;
//			ACBGBlock* tempBlock = World->SpawnActor<ACBGBlock>(Camera->GetComponentLocation(), GetActorRotation(), SpawnParams);
//			tempBlock->SetInitProperty(handBlock->Block);
//			handBlock->Block = Item;
//			handBlock->Empty = false;
//			AddBUFF(Item.ToOwnerBUFF);
//			return true;
//		}
//	}
//	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("Warning!!!"));
//	return false;
//}
//
//void AHerosBase::chooseItem_1()
//{
//	handBlock = &Bag[0];
//}
//void AHerosBase::chooseItem_2()
//{
//	handBlock = &Bag[1];
//}
//void AHerosBase::chooseItem_3()
//{
//	handBlock = &Bag[2];
//}
//
//FVector AHerosBase::GetFireLocation()
//{
//	FVector tempLocation = FVector(0, 0, 0);
//	return tempLocation;
//}
//
//FRotator AHerosBase::GetFireRotation()
//{
//	FRotator tempRotation = FRotator(0, 0, 0);
//	return tempRotation;
//}
//
//void AHerosBase::Fire()
//{
//	if (!handBlock->Empty)
//	{
//		UWorld* World = GetWorld();
//		if (World)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("%s"), *(MineTraceStartArrow->GetComponentLocation()).ToString());
//			ABoltBlock* tempBlock = World->SpawnActor<ABoltBlock>(MineTraceStartArrow->GetComponentLocation(), MineTraceStartArrow->GetComponentRotation());
////			tempBlock->SetInitProperty(handBlock->Block, this);
//			tempBlock->SetFireDirection(MineTraceStartArrow->GetForwardVector(), 1000);
//			handBlock->Empty = true;
//		}
//	}
//}
//
//void AHerosBase::ReloadProperty()
//{
//	//MovementComponent->MaxWalkSpeed = 300.f;
//	//HeroProperty.MoveSpeed
//}
//
//
//void AHerosBase::AddBUFF(FBUFF BUFF)
//{
//	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, TEXT("addBUFF"));
//	myBUFF.Add(BUFF);
//}
//
//void AHerosBase::RunBUFF(float DeltaTime)
//{
//
//	for (int i = 0; i < myBUFF.Num(); i++)
//	{
//		myBUFF[i].LifeTime -= DeltaTime;
//		if (myBUFF[i].LifeTime <= 0)
//		{
//			EndBUFF(i);
//			return;
//		}
//		else if (!myBUFF[i].IsRun)
//		{
//			myBUFF[i].IsRun = true;
//			if (myBUFF[i].xuanyun)
//			{
//				MovementComponent->MaxWalkSpeed = 0;
//			}
//			if (!myBUFF[i].alreadyChangeSpeed)
//				MovementComponent->MaxWalkSpeed *= myBUFF[i].changeSpeed;
//			HeroProperty.LifeValue += myBUFF[i].changeHP * DeltaTime;
//			HeroProperty.Power += myBUFF[i].changePower * DeltaTime;
//
//			myBUFF[i].TempParticle = UGameplayStatics::SpawnEmitterAttached(myBUFF[i].Particle, GetCapsuleComponent());
//		}
//	}
//}
//
//void AHerosBase::EndBUFF(int i)
//{
//
//	if (myBUFF[i].TempParticle)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, TEXT("rEMOVE"));
//		myBUFF[i].TempParticle->DestroyComponent();
//	}
//	myBUFF.RemoveAt(i);
//	ReloadProperty();
//}
//
//void AHerosBase::BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Overlap!"));
//	ACBGBlock* CBGBlock = Cast<ACBGBlock>(OtherActor);
//	if (CBGBlock)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Find!"));
//		AddBlockToPre(CBGBlock);
//	}
//}
//
//void AHerosBase::EndOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, int32 OtherBodyIndex)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("EndOverlap!"));
//	ACBGBlock* CBGBlock = Cast<ACBGBlock>(OtherActor);
//	if (CBGBlock)
//	{
//		RemoveBlockFromPre(CBGBlock);
//	}
//}
//
//void AHerosBase::AddBlockToPre(ACBGBlock* Block)
//{
//	for (int i = 0; i < 3; i++)
//	{
//		if (printBlock[i] == NULL)
//		{
//			printBlock[i] = Block;
//			break;
//		}
//	}
//}
//
//void AHerosBase::RemoveBlockFromPre(ACBGBlock* Block)
//{
//	for (int i = 0; i < 3; i++)
//	{
//		if (printBlock[i] == Block)
//		{
//			printBlock[i] = NULL;
//			break;
//		}
//	}
//}
//
//void AHerosBase::Pressed_R()
//{
//	for (int i = 0; i < 3; i++)
//	{
//		if (printBlock[i] != NULL)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("PreGET!"));
//			if (AddItem(printBlock[i]->BlockProperty))
//			{
//				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("GET!"));
//				printBlock[i]->DestroySelf();
//				printBlock[i] = NULL;
//				break;
//			}
//			else
//			{
//				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GETFalse!"));
//				printBlock[i] = NULL;
//			}
//		}
//	}
//}
//
//void AHerosBase::Released_R()
//{
//	Keyboard_F_Pressed = false;
//}
//
//void AHerosBase::PrintItem(FBlock BlockProperty)
//{
//
//}
//
//void AHerosBase::MineBlock()
//{
//	if (MineTimeCounter >= HeroProperty.MineRate)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Mine"));
//		MineTimeCounter = 0;
//		UWorld* World = GetWorld();
//		if (World)
//		{
//			FHitResult TraceHit;
//			//UE_LOG(LogTemp, Warning, TEXT("起始点：%s"), *(MineTraceStartArrow->GetComponentLocation()).ToString());
//			//UE_LOG(LogTemp, Warning, TEXT("末尾点：%s"), *(MineTraceStartArrow->GetComponentLocation() + MineTraceStartArrow->GetForwardVector() * HeroProperty.MineDistance).ToString());
//			//UE_LOG(LogTemp, Warning, TEXT("距离：%f"), ((MineTraceStartArrow->GetForwardVector() * HeroProperty.MineDistance) - (MineTraceStartArrow->GetComponentLocation())).Size());
//			if (World->LineTraceSingleByChannel(TraceHit, MineTraceStartArrow->GetComponentLocation(), MineTraceStartArrow->GetComponentLocation() + MineTraceStartArrow->GetForwardVector() * HeroProperty.MineDistance, ECollisionChannel::ECC_Visibility))
//			{
//				MineLineTraceResult(TraceHit);
//			}
//		}
//	}
//	else
//		return;
//}
//
//void AHerosBase::MineLineTraceResult(const FHitResult& Hit)
//{
//	ABlockBase* HitBlock = Cast<ABlockBase>(Hit.GetActor());
//	if (HitBlock)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MineHit"));
//		//HitBlock->ApplyPointDamage(this, HeroProperty.BlockDamage);
//	}
//}
//
//void AHerosBase::ApplyPointDamage(AHerosBase* Causer, int32 DamageValue)
//{
//	HeroProperty.LifeValue -= DamageValue;
//	if (HeroProperty.LifeValue <= 0)
//	{
//		Death(Causer);
//	}
//}
//
//void AHerosBase::Death(AHerosBase* Causer)
//{
//	if (GetWorld())
////		GetWorld()->GetAuthGameMode<AMyGameMode>()->PrintKillMessage(Causer, this);
//	this->Destroy(true);
//	return;
//}