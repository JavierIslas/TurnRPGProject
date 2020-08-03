// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT24_API UCombatUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
		void AddPlayerCharacterPanel(class URPGPlayerChar* Target);

	UFUNCTION(BlueprintImplementableEvent, Category = "Combat UI")
	void AddEnemyCharacterPanel(class URPGPlayerChar* Target);
};