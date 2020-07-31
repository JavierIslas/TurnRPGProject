// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGPlayerChar.h"
#include "Engine/DataTable.h"
#include "RPGCombatSystem.h"
#include "ICombatAction.h"
#include "IDecisionMaker.h"
#include "TestCombat.h"
#include "TestDecision.h"

URPGPlayerChar * URPGPlayerChar::CreatePlayerCharacter(FRPGCharacterInfo * CharInfo, UObject * outer)
{
	URPGPlayerChar* Character = NewObject<URPGPlayerChar>(outer);
	
	UDataTable* CharacterClasses = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/Data/CharacterClassInfo.CharacterClassInfo'")));

	if (CharacterClasses == NULL) { UE_LOG(LogTemp, Error, TEXT("Character Classes DataTable not found")); }
	else
	{
		Character->CharacterName = CharInfo->Character_Name;
		FRPGCharClassInfo* Row = CharacterClasses->FindRow<FRPGCharClassInfo>(*(CharInfo->Class_ID), TEXT("LookupCharacterClass"));
		Character->ClassInfo = Row;

		Character->MHP = Character->ClassInfo->StartMHP;
		Character->MMP = Character->ClassInfo->StartMMP;
		Character->CurrentHP = Character->MHP;
		Character->CurrentMP = Character->MMP;

		Character->CurrentATK = Character->ClassInfo->StartATK;
		Character->CurrentDEF = Character->ClassInfo->StartDEF;
		Character->CurrentLuck = Character->ClassInfo->StartLuck;

		Character->DecisionMaker = new TestDecision();
	}
	Character->bIsPlayer = true;
	return Character;
}

URPGPlayerChar* URPGPlayerChar::CreateGameCharacter(FRPGEnemyInfo* EnemyInfo, UObject* outer)
{
	URPGPlayerChar* Character = NewObject<URPGPlayerChar>(outer);

	Character->CharacterName = EnemyInfo->Enemy_Name;
	Character->ClassInfo = nullptr;
	Character->MHP = EnemyInfo->MHP;
	Character->MMP = 0;
	
	Character->CurrentHP = EnemyInfo->MHP;
	Character->CurrentMP = 0;
	
	Character->CurrentATK = EnemyInfo->ATK;
	Character->CurrentDEF = EnemyInfo->DEF;
	Character->CurrentLuck = EnemyInfo->Luck;

	Character->DecisionMaker = new TestDecision();

	return Character;
}

void URPGPlayerChar::BeginDestroy()
{
	Super::BeginDestroy();
	delete(DecisionMaker);
}

void URPGPlayerChar::BeginMakeDecision()
{
	DecisionMaker->BeginMakeDecision(this);
}

bool URPGPlayerChar::MakeDecision(float DeltaSeconds)
{
	return DecisionMaker->MakeDecision(DeltaSeconds);
}

void URPGPlayerChar::BeginExecuteAction()
{
	CombatAction->BeginExecuteAction(this);
}

bool URPGPlayerChar::ExecuteAction(float DeltaSeconds)
{
	bool FinishedAction = CombatAction->ExecuteAction(DeltaSeconds);
	if (FinishedAction) {
		delete(CombatAction);
		return true;
	}
	return false;
}

URPGPlayerChar* URPGPlayerChar::SelectTarget()
{
	URPGPlayerChar* Target = nullptr;
	TArray<URPGPlayerChar*> TargetList = bIsPlayer ? CSInstance->EnemyParty : CSInstance->PlayerParty;
	
	for (URPGPlayerChar* val : TargetList)
	{
		if (val->CurrentHP > 0) {
			Target = val;
			return Target;
		}
	}
	return nullptr;
}
