// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RPGPROJECT24_API ICombatAction
{
public:
	virtual void BeginExecuteAction(class URPGPlayerChar* Character) = 0;

	virtual bool ExecuteAction(float DeltaSeconds) = 0;
};
