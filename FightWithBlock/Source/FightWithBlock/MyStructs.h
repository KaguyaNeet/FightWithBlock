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
	//BUFF编号
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		int32 ID;
	//开发者用的名字
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		FName dName;
	//玩家用的名字
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		FName pName;
	//玩家看的描述
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		FString miaoshu;
	//玩家看的图标
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		UTexture2D* tubiao;
	//BUFF持续时间
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		float LifeTime;
	//BUFF是否晕眩，true为晕眩
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		bool xuanyun;
	//BUFF是否禁锢，true为禁锢
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		bool jingu;
	//BUFF对速度的改变，原速度为1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		float changeSpeed;
	//每秒对生命值的影响
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		float changeHP;
	//增加/减少力量（攻击力）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BUFF")
		float changePower;
};