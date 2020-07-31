// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "FRPGCharacterInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRPGCharacterInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterInfo")
	FString Character_Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterInfo")
	FString Class_ID;

};
