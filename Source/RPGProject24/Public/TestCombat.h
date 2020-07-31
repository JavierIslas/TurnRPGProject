// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICombatAction.h"

class URPGPlayerChar;
/**
 * 
 */
class RPGPROJECT24_API TestCombat : public ICombatAction
{
public:
	TestCombat(URPGPlayerChar* Tar);

	virtual void BeginExecuteAction(URPGPlayerChar* Char) override;

	virtual bool ExecuteAction(float DeltaSeconds) override;

protected:
	float DelayTime;

	URPGPlayerChar* Character;

	URPGPlayerChar* Target;
};
