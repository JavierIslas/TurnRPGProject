// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGPlayerChar.h"

/**
 * 
 */
enum class Phases : uint8
{
	P_Decision,
	P_Action,
	P_Victory,
	P_GameOver,
};

class RPGPROJECT24_API RPGCombatSystem
{
public:
	RPGCombatSystem(TArray<URPGPlayerChar*> PlayerParty, TArray<URPGPlayerChar*> EnemyParty);
	~RPGCombatSystem();

	TArray<URPGPlayerChar*> CombatOrder;
	TArray<URPGPlayerChar*> PlayerParty;
	TArray<URPGPlayerChar*> EnemyParty;

	Phases CombatPhase;

	bool Tick(float DeltaSeconds);

	void CheckForGameOverCondition();

	void CountDeathsForEndCombatPhaseChange();

	void CheckForVictoryCondition();

protected:
	URPGPlayerChar* CurrentTickTarget;
	int TickTargetIndex;
	bool WaitingForCharacter;
	void SetPhase(Phases NewPhase);
	bool GetnextAliveCharacter();
	void SelectNextCharacter();

private: 
	void FreeEnemiesMemory();

	void TargetStartDecision();

	void CheckForDecisionFinish(float DeltaSeconds);

	void CheckForExecuteFinish(float DeltaSeconds);

	void TargetStartExecute();

	void GiveCharacterPosition(TArray<URPGPlayerChar*>& Party);

	void ClearCombatSystemFromPlayerChar();

	int CountDeathsOnParty(TArray<URPGPlayerChar*> Party);
};
