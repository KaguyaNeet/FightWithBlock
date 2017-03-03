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
struct FstructBUFF : public FTableRowBase
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
		float changeHP;
	//����/������������������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		float changePower;
};