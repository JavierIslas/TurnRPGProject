// Fill out your copyright notice in the Description page of Project Settings.

#include "TestDecision.h"
#include "RPGPlayerChar.h"
#include "TestCombat.h"

void TestDecision::BeginMakeDecision(URPGPlayerChar* Character)
{
	Character->CombatAction = new TestCombat(Character->SelectTarget());
}

bool TestDecision::MakeDecision(float DeltaSeconds)
{
	return true;
}
