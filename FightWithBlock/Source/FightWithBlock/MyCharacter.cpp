// Fill out your copyright notice in the Description page of Project Settings.

#include "FightWithBlock.h"
#include "MyCharacter.h"
#include "BlockBase.h"
#include "NET/UnrealNetwork.h"
#include "MyGameInstance.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bReplicateMovement = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);

	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MyCamera->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	MyCamera->AttachTo(CameraBoom);
	MyCamera->bUsePawnControlRotation = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> FPSSkeletalMesh(TEXT("SkeletalMesh'/Game/FirstPerson/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'"));
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("myFPSMesh"));
	FPSMesh->AttachTo(RootComponent);
	FPSMesh->SetSkeletalMesh(FPSSkeletalMesh.Object);
	FPSMesh->SetRelativeLocation(FVector(0, 0, -170));
	FPSMesh->SetRelativeRotation(FRotator(0, -90, 0));
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;
	FPSMesh->SetOnlyOwnerSee(true);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> TPSSkeletalMesh(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	//ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBlueprint(TEXT("AnimBlueprint'/Game/myBlueprint/CharacterBP.CharacterBP'"));
	GetMesh()->SetSkeletalMesh(TPSSkeletalMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	if (Role == ROLE_Authority)
	{
		GetMesh()->bIsAutonomousTickPose = false;
	}
	else
	{
		GetMesh()->bIsAutonomousTickPose = true;
	}
	//if (AnimBlueprint.Succeeded())
	//{
	//	GetMesh()->SetAnimInstanceClass(AnimBlueprint.Object->GeneratedClass);
	//}

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::BeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMyCharacter::EndOverlap);


	MineTraceStartArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("MineTraceStartArrow"));
	MineTraceStartArrow->AttachTo(MyCamera);
	MineTraceStartArrow->SetRelativeLocation(FVector(0, 0, 0));
	MineTraceStartArrow->SetHiddenInGame(true);

	//AutoPossessPlayer = EAutoReceiveInput::Player0;
	//测试用要删的！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	//多打几行引起注意！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	//HeroInitProperty.LifeValue = HeroInitProperty.MaxLifeValue;
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
	if (Role == ROLE_Authority)
	{
		isAuth = true;
	}
	IsCampFull = true;
	MyCamp = ECamp::EDefault;
	AddUI();
	//ChooseHUDLifeValue(HeroInitProperty.LifeValue / HeroInitProperty.MaxLifeValue);
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("this is MyCharacter!"));	
	}
	SetNowChoose(1);
	handBlock = &Bag[0];
	//if (Role == ROLE_Authority)
	//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("ROLE_Authority!!!!!!!!!!"));
	//if (Role == ROLE_AutonomousProxy)
	//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("ROLE_AutonomousProxy!!!!!!!!!!"));
	//if (Role == ROLE_SimulatedProxy)
	//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Black, TEXT("ROLE_SimulatedProxy!!!!!!!!!!"));
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

	PlayerInputComponent->BindAxis("TurnX", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnY", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Item_1", IE_Pressed, this, &AMyCharacter::chooseItem_1);
	PlayerInputComponent->BindAction("Item_2", IE_Pressed, this, &AMyCharacter::chooseItem_2);
	PlayerInputComponent->BindAction("Item_3", IE_Pressed, this, &AMyCharacter::chooseItem_3);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Fire);
	PlayerInputComponent->BindAction("GetItem", IE_Pressed, this, &AMyCharacter::Pressed_R);
	PlayerInputComponent->BindAction("GetItem", IE_Released, this, &AMyCharacter::Released_R);
	PlayerInputComponent->BindAction("MineBlock", IE_Pressed, this, &AMyCharacter::MineBlock);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);

}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AMyCharacter, MyCamp);
	//DOREPLIFETIME(AMyCharacter, handBlock);
	DOREPLIFETIME(AMyCharacter, myBUFF);
	DOREPLIFETIME(AMyCharacter, HeroProperty);
	
	DOREPLIFETIME(AMyCharacter, Bag);
	DOREPLIFETIME(AMyCharacter, MyCamera);
	DOREPLIFETIME(AMyCharacter, IsCampFull);
	DOREPLIFETIME(AMyCharacter, CharacterName);
}


void AMyCharacter::ClientAddBlockUI_Implementation(int Choose, FBlock Item)
{
	AddBlockUI(Choose, Item);
}
bool AMyCharacter::ClientAddBlockUI_Validate(int Choose, FBlock Item)
{
	return true;
}

void AMyCharacter::ClientRemoveBlockUI_Implementation(int Choose)
{
	RemoveBlockUI(Choose);
}
bool AMyCharacter::ClientRemoveBlockUI_Validate(int Choose)
{
	return true;
}

bool AMyCharacter::AddItem(FBlock Item)
{
	for (int i = 0; i < BAGSPACE; i++)
	{
		if (Bag[i].Empty)
		{
			ClientAddBlockUI(i + 1, Item);
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
			//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("FULL!!!"));
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			ACBGBlock* tempBlock = World->SpawnActor<ACBGBlock>(MyCamera->GetComponentLocation(), GetActorRotation(), SpawnParams);
			tempBlock->SetInitProperty(handBlock->Block);
			ClientRemoveBlockUI(NowChoose);
			ClientAddBlockUI(NowChoose, Item);
			handBlock->Block = Item;
			handBlock->Empty = false;
			AddBUFF(Item.ToOwnerBUFF);
			return true;
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("Warning!!!"));
	return false;
}


void AMyCharacter::chooseItem_1()
{
	SetNowChoose(1);
	handBlock = &Bag[0];
	NowChooseUI(NowChoose);
	ServerChooseItem_1();
}
void AMyCharacter::ServerChooseItem_1_Implementation()
{
	handBlock = &Bag[0];
}
bool AMyCharacter::ServerChooseItem_1_Validate()
{
	return true;
}

void AMyCharacter::chooseItem_2()
{
	SetNowChoose(2);
	handBlock = &Bag[1];
	NowChooseUI(NowChoose);
	ServerChooseItem_2();
}
void AMyCharacter::ServerChooseItem_2_Implementation()
{
	handBlock = &Bag[1];
}
bool AMyCharacter::ServerChooseItem_2_Validate()
{
	return true;
}

void AMyCharacter::chooseItem_3()
{
	SetNowChoose(3);
	handBlock = &Bag[2];
	NowChooseUI(NowChoose);
	ServerChooseItem_3();
}
void AMyCharacter::ServerChooseItem_3_Implementation()
{
	handBlock = &Bag[2];
}
bool AMyCharacter::ServerChooseItem_3_Validate()
{
	return true;
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

void AMyCharacter::Fire_()
{
	if (Role == ROLE_Authority)
	{
		if (!handBlock->Empty)
		{
			UWorld* World = GetWorld();
			if (World)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("FIRE!!!!!!!!!!"));
				//UE_LOG(LogTemp, Warning, TEXT("%s"), *(MineTraceStartArrow->GetComponentLocation()).ToString());
				ABoltBlock* tempBlock = World->SpawnActor<ABoltBlock>(MineTraceStartArrow->GetComponentLocation(), MyCamera->GetComponentRotation());
				tempBlock->SetInitProperty(handBlock->Block, this);
				tempBlock->SetFireDirection(MineTraceStartArrow->GetForwardVector(), 1000);
				handBlock->Empty = true;
			}
		}
	}
}
void AMyCharacter::Fire()
{
	if (Role < ROLE_Authority)
	{
		SetCamera();
		ServerFire();
	}
	else
	{
		ServerFire_Implementation();
	}
	ClientRemoveBlockUI(NowChoose);
}
void AMyCharacter::ServerFire_Implementation()
{
	MulticastFire();
}
bool AMyCharacter::ServerFire_Validate()
{
	return true;
}
void AMyCharacter::MulticastFire_Implementation()
{
	BlueprintFire();
}
bool AMyCharacter::MulticastFire_Validate()
{
	return true;
}

void AMyCharacter::ReloadProperty()
{
	//MovementComponent->MaxWalkSpeed = 300.f;
	//HeroProperty.MoveSpeed
}


void AMyCharacter::AddBUFF(FBUFF BUFF)
{
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, TEXT("addBUFF"));
		myBUFF.Add(BUFF);
}

void AMyCharacter::RunBUFF(float DeltaTime)
{
	
	for (int i = 0; i < myBUFF.Num(); i++)
	{
		myBUFF[i].LifeTime -= DeltaTime;
		if (myBUFF[i].LifeTime <= 0)
		{
			EndBUFF(i);
			return;
		}
		else if(!myBUFF[i].IsRun)
		{
			myBUFF[i].IsRun = true;
			if (myBUFF[i].xuanyun)
			{
				MovementComponent->MaxWalkSpeed = 0;
			}
			if (!myBUFF[i].alreadyChangeSpeed)
				MovementComponent->MaxWalkSpeed *= myBUFF[i].changeSpeed;
			HeroProperty.LifeValue += myBUFF[i].changeHP * DeltaTime;
			HeroProperty.Power += myBUFF[i].changePower * DeltaTime;
			
			myBUFF[i].TempParticle = UGameplayStatics::SpawnEmitterAttached(myBUFF[i].Particle, GetCapsuleComponent());
		}
	}
}

void AMyCharacter::EndBUFF(int i)
{
	
	if (myBUFF[i].TempParticle)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, TEXT("rEMOVE"));
		myBUFF[i].TempParticle->DestroyComponent();
	}
	myBUFF.RemoveAt(i);
	ReloadProperty();
}

void AMyCharacter::BeginOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, int32 OtherBodyIndex, bool FromSweep, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Overlap!"));
	ACBGBlock* CBGBlock = Cast<ACBGBlock>(OtherActor);
	if (CBGBlock)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Find!"));
		AddBlockToPre(CBGBlock);
	}
}

void AMyCharacter::EndOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherCompnent, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("EndOverlap!"));
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

void AMyCharacter::Pressed_R_()
{
	for (int i = 0; i < 3; i++)
	{
		if (printBlock[i] != NULL)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("PreGET!"));
			if (AddItem(printBlock[i]->BlockProperty))
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("GET!"));
				printBlock[i]->DestroySelf();
				printBlock[i] = NULL;
				break;
			}
			else
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GETFalse!"));
				printBlock[i] = NULL;
			}
		}
	}
}
void AMyCharacter::Pressed_R()
{
	if (Role < ROLE_Authority)
	{
		ServerPressed_R();
	}
	else
	{
		ServerPressed_R_Implementation();
	}
}
void AMyCharacter::ServerPressed_R_Implementation()
{
	Pressed_R_();
}
bool AMyCharacter::ServerPressed_R_Validate()
{
	return true;
}

void AMyCharacter::Released_R()
{
	Keyboard_F_Pressed = false;
}

void AMyCharacter::PrintItem(FBlock BlockProperty)
{

}

void AMyCharacter::MineBlock_()
{
	BlueprintMineBlock();
}
void AMyCharacter::MineBlock()
{
	ServerMineBlock();
}
void AMyCharacter::ServerMineBlock_Implementation()
{
	MulticastMineBlock();
}
bool AMyCharacter::ServerMineBlock_Validate()
{
	return true;
}
void AMyCharacter::MulticastMineBlock_Implementation()
{
	MineBlock_();
}
bool AMyCharacter::MulticastMineBlock_Validate()
{
	return true;
}

void AMyCharacter::MineLineTraceResult(const FHitResult& Hit)
{
	ABlockBase* HitBlock = Cast<ABlockBase>(Hit.GetActor());
	if (HitBlock)
	{
		BlueprintSpawmEmitter();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MineHit"));
		HitBlock->ApplyPointDamage(this, HeroProperty.BlockDamage);
		
	}
}
void AMyCharacter::MulticastSpawnEmitter_Implementation(UParticleSystem* Particle, FVector Location)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, FTransform(Location));
}
bool AMyCharacter::MulticastSpawnEmitter_Validate(UParticleSystem* Particle, FVector Location)
{
	return true;
}

void AMyCharacter::MulticastPlayAudio_Implementation(USoundBase* Sound, FVector Location)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location);
}
bool AMyCharacter::MulticastPlayAudio_Validate(USoundBase* Sound, FVector Location)
{
	return true;
}

void AMyCharacter::ApplyPointDamage_(AMyCharacter* Causer, int32 DamageValue)
{
	MulticastShakeCamera();
	HeroProperty.LifeValue -= DamageValue;
	//ChooseHUDLifeValue(HeroInitProperty.LifeValue / HeroInitProperty.MaxLifeValue);
	if (Role < ROLE_AutonomousProxy)
	{
		ChooseLifeBar(HeroInitProperty.LifeValue / HeroInitProperty.MaxLifeValue);
	}
	else
	{
		ChooseUILife(HeroInitProperty.LifeValue / HeroInitProperty.MaxLifeValue);
	}
	UE_LOG(LogTemp, Warning, TEXT("Life:%f, Damage:%f"), HeroProperty.LifeValue, DamageValue);
	if (HeroProperty.LifeValue <= 0)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Death"));
		Death(Causer);
	}
}
void AMyCharacter::ApplyPointDamage(AMyCharacter* Causer, int32 DamageValue)
{
	if (Role < ROLE_Authority)
	{
		ServerApplyPointDamage(Causer, DamageValue);
	}
	else
	{
		ServerApplyPointDamage_Implementation(Causer, DamageValue);
	}
}
void AMyCharacter::ServerApplyPointDamage_Implementation(AMyCharacter* Causer, int32 DamageValue)
{
	ApplyPointDamage_(Causer, DamageValue);
}
bool AMyCharacter::ServerApplyPointDamage_Validate(AMyCharacter* Causer, int32 DamageValue)
{
	return true;
}

void AMyCharacter::MulticastReBorn_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetSimulatePhysics(false);
}
bool AMyCharacter::MulticastReBorn_Validate()
{
	return true;
}
void AMyCharacter::ReBorn()
{
	if (Role == ROLE_Authority)
	{
		MulticastReBorn();
	}
}

void AMyCharacter::ClientDeath_Implementation()
{
	//if (GetWorld())
	//	GetWorld()->GetAuthGameMode<AMyGameMode>()->PrintKillMessage(Causer, this);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
	return;
}
bool AMyCharacter::ClientDeath_Validate()
{
	return true;
}

void AMyCharacter::Death(AMyCharacter* Causer)
{
	if (Role == ROLE_Authority)
	{
		ClientDeath();
		
		UGameInstance* GameInstance = GetGameInstance();
		if (GameInstance)
		{
			UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
			//MyGameInstance->ApplyKill(MyCamp);
		}
	}
}

void AMyCharacter::ServerSetCamera_Implementation(FRotator Rotation)
{
	SetCameraRotation(Rotation);
}
bool AMyCharacter::ServerSetCamera_Validate(FRotator Rotation)
{
	return true;
}
void AMyCharacter::SetCamera()
{
	if (Role < ROLE_Authority)
	{
		ServerSetCamera(MyCamera->GetComponentRotation());
	}
}
void AMyCharacter::SetCameraRotation(FRotator Rotation)
{
	MyCamera->SetWorldRotation(Rotation);
}

void AMyCharacter::AddUI()
{
	if (Role < ROLE_AutonomousProxy)
	{
		CreateLifeBar();
	}
	else
	{
		CreateUI();
	}
	if (Role == ROLE_Authority)
	{
		CreateLifeBar();
	}
}

void AMyCharacter::SetNowChoose(int Choose)
{
	if (Choose > 0 && Choose < 4)
	{
		NowChoose = Choose;
		return;
	}
	return;
}


void AMyCharacter::MulticastRefreshLifeBar_Implementation()
{
	RefreshLifeBar_();
}
bool AMyCharacter::MulticastRefreshLifeBar_Validate()
{
	return true;
}

void AMyCharacter::RefreshLifeBar()
{
	if (Role == ROLE_Authority)
	{
		MulticastRefreshLifeBar();
	}
}

void AMyCharacter::ControllerInit(ECamp Camp, FString Name)
{

}

//void AMyCharacter::SetName(FName Name_)
//{
//	ServerSetName(Name_);
//}
//void AMyCharacter::ServerSetName_Implementation(FName Name_)
//{
//		HeroName = Name_;
//}
//bool AMyCharacter::ServerSetName_Validate(FName Name_)
//{
//	return true;
//}

void AMyCharacter::MulticastShakeCamera_Implementation()
{
	ShakeCamera();
}
bool AMyCharacter::MulticastShakeCamera_Validate()
{
	return true;
}

void AMyCharacter::ServerSetCamp_Implementation(ECamp Camp)
{
	MyCamp = Camp;
}
bool AMyCharacter::ServerSetCamp_Validate(ECamp Camp)
{
	return true;
}

void AMyCharacter::SetCamp(ECamp Camp)
{
	ServerSetCamp(Camp);
}

void AMyCharacter::ClientSetAllowInput_Implementation(bool Choose)
{
	if (Role >= ROLE_AutonomousProxy)
	{
		SetAllowInput(Choose);
	}
}
bool AMyCharacter::ClientSetAllowInput_Validate(bool Choose)
{
	return true;
}

void AMyCharacter::ServerSetSpeed_Implementation(float Speed)
{
	MulticastSetSpeed(Speed);
}
bool AMyCharacter::ServerSetSpeed_Validate(float Speed)
{
	return true;
}

void AMyCharacter::MulticastSetSpeed_Implementation(float Speed)
{
	if (UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent()))
	{
		MovementComponent->MaxWalkSpeed = Speed;
	}
}
bool AMyCharacter::MulticastSetSpeed_Validate(float Speed)
{
	return true;
}