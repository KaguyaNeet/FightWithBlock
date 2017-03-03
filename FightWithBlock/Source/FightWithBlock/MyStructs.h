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
	//BUFF���
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		int32 ID;
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
		float LifeTime;
	//BUFF�Ƿ���ѣ��trueΪ��ѣ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		bool xuanyun;
	//BUFF�Ƿ������trueΪ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		bool jingu;
	//BUFF���ٶȵĸı䣬ԭ�ٶ�Ϊ1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		float changeSpeed;
	//ÿ�������ֵ��Ӱ��
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		int32 changeHP;
	//����/������������������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		int32 changePower;
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
		FName dName;
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
		int32 LifeValue;
	//li liang zhi
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		int32 Power;
	//yi dong su du
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hero")
		float MoveSpeed;
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
		float Size;
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

};

