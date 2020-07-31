// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGPlayerChar.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT24_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()

	URPGGameInstance(const class FObjectInitializer& ObjectInitializer);

protected:
	bool bIsInitialized;

public:
	TArray<URPGPlayerChar*> PartyMember;

	void Init();
};
