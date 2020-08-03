// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGProject24GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RPGPROJECT24_API ARPGProject24GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public: 
	ARPGProject24GameModeBase(const class FObjectInitializer& ObjectInitializer);

	class RPGCombatSystem* CSInstance = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TArray<class URPGPlayerChar*> EnemyParty;

	UPROPERTY()
	class UCombatUIWidget* CombatUIInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UCombatUIWidget> CombatUIClass;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION(exec)
	void TestCombat();
};
