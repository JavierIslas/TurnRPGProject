// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class RPGPROJECT24_API IDecisionMaker
{
public:
	virtual void BeginMakeDecision(class URPGPlayerChar* Character) = 0;

	virtual bool MakeDecision(float DeltaSeconds) = 0;
};
