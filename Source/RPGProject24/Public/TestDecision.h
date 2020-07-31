// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDecisionMaker.h"

/**
 * 
 */
class RPGPROJECT24_API TestDecision : public IDecisionMaker
{
public:
	virtual void BeginMakeDecision(class URPGPlayerChar* Character);

	virtual bool MakeDecision(float DeltaSeconds);
};
