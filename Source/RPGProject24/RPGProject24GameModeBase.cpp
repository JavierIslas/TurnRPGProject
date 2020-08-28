// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RPGProject24GameModeBase.h"
#include "UObject/UObjectGlobals.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "CombatUIWidget.h"
#include "Public/RPGCharacter.h"
#include "Public/RPGGameInstance.h"
#include "Public/RPGCombatSystem.h"
#include "Public/FRPGEnemyInfo.h"

ARPGProject24GameModeBase::ARPGProject24GameModeBase(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	
	DefaultPawnClass = ARPGCharacter::StaticClass();
}

void ARPGProject24GameModeBase::BeginPlay()
{
	Cast<URPGGameInstance>(GetGameInstance())->Init();
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ARPGProject24GameModeBase::Tick(float DeltaTime)
{
	if (CSInstance)
	{
		
		if (bool CombatOver = CSInstance->Tick(DeltaTime))
		{
			if (CSInstance->CombatPhase == Phases::P_GameOver)
			{
				UE_LOG(LogTemp, Log, TEXT("Player loses combat, Game Over"));
			}
			else
			{
				if (CSInstance->CombatPhase == Phases::P_Victory)
					UE_LOG(LogTemp, Log, TEXT("Player wins Combat"));
			}

			//Destroy the DecisionMaker from player's Characters
			for (URPGPlayerChar* var : CSInstance->PlayerParty) {
				var->DecisionMaker = nullptr;
			}

			UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

			//returns control to the player controller
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetActorTickEnabled(true);

			CombatUIInstance->RemoveFromViewport();
			CombatUIInstance = nullptr;
			delete(CSInstance);
			CSInstance = nullptr;
			EnemyParty.Empty();
		}
	}
}

void ARPGProject24GameModeBase::TestCombat()
{
	//Located Enemies asset
	UDataTable* EnemyTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/Data/EnemyInformation.EnemyInformation'")));
	if (!EnemyTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemies data not found"));
		return;
	}


	//Locate Enemy
	FRPGEnemyInfo* Row = EnemyTable->FindRow<FRPGEnemyInfo>(TEXT("S1"), TEXT("LookupEnemyInfo"));

	if (!Row)
	{
		UE_LOG(LogTemp, Error, TEXT("Enemy ID not found"));
		return;
	}

	//Disable Player Actor
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetActorTickEnabled(false);

	//Add Enemies to the party
	URPGPlayerChar* Enemy = URPGPlayerChar::CreateGameCharacter(Row, this);
	EnemyParty.Add(Enemy);

	URPGGameInstance* GI = Cast<URPGGameInstance>(GetGameInstance());
	CSInstance = new RPGCombatSystem(GI->PartyMember, EnemyParty);
	UE_LOG(LogTemp, Log, TEXT("Combat Started"));

	//Instance of the UI widget
	CombatUIInstance = CreateWidget<UCombatUIWidget>(GetGameInstance(), CombatUIClass);
	CombatUIInstance->AddToViewport();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	for (URPGPlayerChar* var : GI->PartyMember) {
		CombatUIInstance->AddPlayerCharacterPanel(var);
		var->DecisionMaker = CombatUIInstance;
	}

	for (URPGPlayerChar* var : EnemyParty) {
		CombatUIInstance->AddEnemyCharacterPanel(var);
	}
}
