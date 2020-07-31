// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "FRPGEnemyInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FRPGEnemyInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyInfo")
	FString Enemy_Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyInfo")
	int32 MHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyInfo")
	int32 ATK;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyInfo")
	int32 DEF;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyInfo")
	int32 Luck;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "EnemyInfo")
	TArray<FString> Abilities;
};