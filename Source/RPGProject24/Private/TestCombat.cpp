// Fill out your copyright notice in the Description page of Project Settings.

#include "TestCombat.h"
#include "RPGPlayerChar.h"

TestCombat::TestCombat(URPGPlayerChar* Targ)
{
	Target = Targ;
}

void TestCombat::BeginExecuteAction(URPGPlayerChar* Char)
{
	Character = Char;

	//The Target is dead, need a new one
	if (Target->CurrentHP <= 0)
	{
		Target = Character->SelectTarget();
	}

	//No targect, return
	if (Target == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("%s attacts %s"), *Char->CharacterName, *Target->CharacterName);
	Target->CurrentHP -= 5;
	DelayTime = 1.0f;
}

bool TestCombat::ExecuteAction(float DeltaSeconds)
{
	DelayTime -= DeltaSeconds;
	return DelayTime <= 0.0f;
}
