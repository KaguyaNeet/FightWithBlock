// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Engine/DataTable.h"
#include "MyStructs.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTWITHBLOCK_API UMyStructs : public UDataTable
{
	GENERATED_BODY()
	
	
	
	
};

USTRUCT()
struct FPosition : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Position")
		int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Position")
		int32 Y;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Position")
		int32 Z;
};

USTRUCT()
struct FBUFF : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		bool NotEmpty = false;

	bool IsRun = false;
	//BUFF���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		int32 ID = 1;
	//�������õ�����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		FName dName;
	//����õ�����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		FName pName;
	//��ҿ�������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		FString miaoshu;
	//��ҿ���ͼ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		UTexture2D* tubiao;
	//BUFF����ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		float LifeTime = 0;
	//BUFF�Ƿ���ѣ��trueΪ��ѣ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		bool xuanyun;
	//BUFF�Ƿ������trueΪ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		bool jingu;
	//BUFF���ٶȵĸı䣬ԭ�ٶ�Ϊ1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		float changeSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		bool alreadyChangeSpeed = true;
	//ÿ�������ֵ��Ӱ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		int32 changeHP;
	//����/������������������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		int32 changePower;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		UParticleSystem* Particle;
	UParticleSystemComponent* TempParticle = NULL;
};

USTRUCT()
struct FHero : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

	//ying xiong de bian hao
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		int32 ID;
	//kai fa zhe yong de ming zi
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		FName dName = TEXT("Hero!");
	//wan jia kan dao de ming zi
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		FName pName;
	//ying xiong de jian jie
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		FString miaoshu;
	//tu biao
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		UTexture2D* tubiao;
	//sheng ming zhi
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		int32 LifeValue = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		int32 MaxLifeValue = 10;
	//li liang zhi
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		int32 Power;
	//yi dong su du
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		float MoveSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		float MineDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		float MineRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		int32 BlockDamage;
};

USTRUCT()
struct FBlock : public FTableRowBase
{
	
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		int32 ID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		FName dName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		FName pName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		FString miaoshu;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		UTexture2D* tubiao;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		UStaticMesh* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		UMaterial* Material;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		FPosition Position;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		float Size = 0.1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		int32 LifeValue = 3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		int32 DamageValue = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		int32 ExplosionDamageValue;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		float InitialSpeed = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		UParticleSystem* selfParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		UParticleSystem* handParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		UParticleSystem* breakParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		UParticleSystem* traceParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		UParticleSystem* explosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		FBUFF ToMinerBUFF;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		FBUFF ToOwnerBUFF;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block")
		FBUFF ToEnemyBUFF;
};

USTRUCT()
struct FItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		bool Empty = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FBlock Block;
};



