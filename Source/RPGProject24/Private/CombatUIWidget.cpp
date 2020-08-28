// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGPlayerChar.h"
#include "RPGCombatSystem.h"
#include "TestCombat.h"
#include "CombatUIWidget.h"

TArray<URPGPlayerChar*> UCombatUIWidget::GetCharacterTargets()
{
	if (CurrentTarget->bIsPlayer)
	{
		return CurrentTarget->CSInstance->EnemyParty;
	}
	return CurrentTarget->CSInstance->PlayerParty;
}

void UCombatUIWidget::AttackTarget(URPGPlayerChar* Target)
{
	TestCombat* Action = new TestCombat(Target);
	CurrentTarget->CombatAction = Action;
	bFinishedDecision = true;
}

void UCombatUIWidget::BeginMakeDecision(URPGPlayerChar* Target)
{
	CurrentTarget = Target;
	bFinishedDecision = false;
	ShowActionsPanel(Target);

}

bool UCombatUIWidget::MakeDecision(float DeltaSeconds)
{
	return bFinishedDecision;
}
