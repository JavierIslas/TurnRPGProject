// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IDecisionMaker.h"
#include "CombatUIWidget.generated.h"

class URPGPlayerChar;

/**
 * 
 */
UCLASS()
class RPGPROJECT24_API UCombatUIWidget : public UUserWidget, public IDecisionMaker
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
	void AddPlayerCharacterPanel(URPGPlayerChar* Target);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
	void AddEnemyCharacterPanel(URPGPlayerChar* Target);

	UFUNCTION(BlueprintCallable, Category = "Combat UI")
	TArray<URPGPlayerChar*> GetCharacterTargets();

	UFUNCTION(BlueprintCallable, Category = "Combat UI")
	void AttackTarget(URPGPlayerChar* Target);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
	void ShowActionsPanel(URPGPlayerChar* Target);

	void BeginMakeDecision(URPGPlayerChar* Target);
	bool MakeDecision(float DeltaSeconds);

protected:
	URPGPlayerChar* CurrentTarget = nullptr;

	bool bFinishedDecision;
};