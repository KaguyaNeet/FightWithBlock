// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/UserDefinedEnum.h"
#include "MyEnums.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTWITHBLOCK_API UMyEnums : public UUserDefinedEnum
{
	GENERATED_BODY()
	
	
	
	
};

UENUM(BlueprintType)
enum class ECamp: uint8
{
	EBlue UMETA(DisplayName = "Blue"),
	ERed UMETA(DisplayName = "Red"),
	EDefault UMETA(DisplayName = "neutral")
};