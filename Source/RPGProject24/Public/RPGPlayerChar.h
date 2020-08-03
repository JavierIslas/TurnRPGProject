// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Public/FRPGCharacterInfo.h"
#include "../Public/FRPGCharClassInfo.h"
#include "../Public/FRPGEnemyInfo.h"
#include "RPGPlayerChar.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RPGPROJECT24_API URPGPlayerChar : public UObject
{
	GENERATED_BODY()
	
public:
	FRPGCharClassInfo* ClassInfo = NULL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	int32 MHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	int32 MMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	int32 CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	int32 CurrentMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	int32 CurrentATK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	int32 CurrentDEF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterInfo")
	int32 CurrentLuck;

	bool bIsPlayer = false;

	class RPGCombatSystem* CSInstance = NULL;

	static URPGPlayerChar* CreatePlayerCharacter(FRPGCharacterInfo* CharInfo, UObject* outer);

	static URPGPlayerChar* CreateGameCharacter(FRPGEnemyInfo* EnemyInfo, UObject* outer);

	class ICombatAction* CombatAction;

	class IDecisionMaker* DecisionMaker;

	void BeginDestroy() override;

	void BeginMakeDecision();
	bool MakeDecision(float DeltaSeconds);

	void BeginExecuteAction();
	bool ExecuteAction(float DeltaSeconds);

	URPGPlayerChar* SelectTarget();
	
protected:
	float TestDelayTimer;

};
