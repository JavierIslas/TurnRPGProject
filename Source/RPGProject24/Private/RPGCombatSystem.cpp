// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCombatSystem.h"

void RPGCombatSystem::GiveCharacterPosition(TArray<URPGPlayerChar*>& Party)
{
	for (URPGPlayerChar* var : Party)
	{
		CombatOrder.Add(var);
		var->CSInstance = this;
	}
}

RPGCombatSystem::RPGCombatSystem(TArray<URPGPlayerChar*> PlayerParty, TArray<URPGPlayerChar*> EnemyParty)
{
	this->PlayerParty = PlayerParty;
	this->EnemyParty = EnemyParty;

	GiveCharacterPosition(PlayerParty);

	GiveCharacterPosition(EnemyParty);

	TickTargetIndex = 0;

	SetPhase(Phases::P_Decision);

}

void RPGCombatSystem::FreeEnemiesMemory()
{
	//Free Enemies Memory
	for (int i = 0; i < EnemyParty.Num(); ++i)
	{
		EnemyParty[i] = nullptr;
	}
}

void RPGCombatSystem::ClearCombatSystemFromPlayerChar()
{
	for (URPGPlayerChar* var : CombatOrder)
	{
		var->CSInstance = nullptr;
	}
}

RPGCombatSystem::~RPGCombatSystem()
{
	FreeEnemiesMemory();
	ClearCombatSystemFromPlayerChar();
}

void RPGCombatSystem::TargetStartDecision()
{
	CurrentTickTarget->BeginMakeDecision();
	WaitingForCharacter = true;
}

void RPGCombatSystem::CheckForDecisionFinish(float DeltaSeconds)
{
	bool DecisionMade = CurrentTickTarget->MakeDecision(DeltaSeconds);
	if (DecisionMade)
	{
		SelectNextCharacter();
		//No more Characters, switch to P_Action
		if (TickTargetIndex == -1)
			SetPhase(Phases::P_Action);
	}
}

bool RPGCombatSystem::Tick(float DeltaSeconds)
{
	switch (CombatPhase)
	{
	case Phases::P_Decision: {
		//Ask CurrentChar to make decision
		if (!WaitingForCharacter)
		{
			TargetStartDecision();
		}
		CheckForDecisionFinish(DeltaSeconds);
	}
		break;
	case Phases::P_Action:
	{
		//CurrentChar execute Decision
		if (!WaitingForCharacter)
		{
			TargetStartExecute();
		}
		CheckForExecuteFinish(DeltaSeconds);
	}
		break;
	case Phases::P_Victory:
	case Phases::P_GameOver:
		return true;
		break;
	default:
		break;
	}

	CountDeathsForEndCombatPhaseChange();
	return false;
}

int RPGCombatSystem::CountDeathsOnParty(TArray<URPGPlayerChar*> Party)
{
	int DeadCount = 0;
	for (URPGPlayerChar* var : Party)
	{
		if (var->CurrentHP <= 0)
			++DeadCount;
	}
	return DeadCount;
}

void RPGCombatSystem::CheckForGameOverCondition(int& DeadCount)
{
	if (CountDeathsOnParty(PlayerParty) == PlayerParty.Num())
	{
		SetPhase(Phases::P_GameOver);
	}
}

void RPGCombatSystem::CheckForVictoryCondition(int& DeadCount)
{
	if (CountDeathsOnParty(EnemyParty) == EnemyParty.Num())
	{
		SetPhase(Phases::P_Victory);
	}
}

void RPGCombatSystem::CountDeathsForEndCombatPhaseChange()
{
	int DeadCount = 0;
	CheckForGameOverCondition(DeadCount);

	DeadCount = 0;
	CheckForVictoryCondition(DeadCount);
}

void RPGCombatSystem::CheckForExecuteFinish(float DeltaSeconds)
{
	bool ActionFinished = CurrentTickTarget->ExecuteAction(DeltaSeconds);
	//when Action executed
	if (ActionFinished)
	{
		SelectNextCharacter();
		//No more Characters, go to P_Decision
		if (TickTargetIndex == -1)
			SetPhase(Phases::P_Decision);
	}
}

void RPGCombatSystem::TargetStartExecute()
{
	CurrentTickTarget->BeginExecuteAction();
	WaitingForCharacter = true;
}

void RPGCombatSystem::SetPhase(Phases NewPhase)
{
	CombatPhase = NewPhase;

	switch (NewPhase)
	{
	case Phases::P_Decision:
	case Phases::P_Action:
		TickTargetIndex = 0;
		SelectNextCharacter();
		break;
	case Phases::P_Victory:
		//Handle Victory
		break;
	case Phases::P_GameOver:
		//Handle GameOver
		break;
	default:
		break;
	}
}

void RPGCombatSystem::SelectNextCharacter()
{
	WaitingForCharacter = false;

	for (int i = TickTargetIndex; i < CombatOrder.Num(); ++i)
	{
		URPGPlayerChar* Character = CombatOrder[i];
		if (Character->CurrentHP > 0)
		{
			TickTargetIndex = i + 1;
			CurrentTickTarget = Character;
			return;
		}
	}

	TickTargetIndex = -1;
	CurrentTickTarget = nullptr;
}