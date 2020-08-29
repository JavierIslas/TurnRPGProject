// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGGameInstance.h"
#include "UObject/UObjectGlobals.h"
#include "FRPGCharacterInfo.h"

URPGGameInstance::URPGGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){
	bIsInitialized = false;
}

void URPGGameInstance::Init()
{
	if (bIsInitialized) return;

	bIsInitialized = true;

	UDataTable* Characters = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, TEXT("DataTable'/Game/Data/CharacterInformation.CharacterInformation'")));
	if (Characters == NULL) {
		UE_LOG(LogTemp, Error, TEXT("Character data table not found"));
		return;
	}

	FRPGCharacterInfo* Row = Characters->FindRow<FRPGCharacterInfo>(TEXT("Player1"), TEXT("LookupCharacterClass"));
	if (Row == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Character ID 'Player1' not found"));
		return;
	}

	PartyMember.Add(URPGPlayerChar::CreatePlayerCharacter(Row, this));

}

void URPGGameInstance::PrepareReset()
{
	bIsInitialized = false;
	PartyMember.Empty();
}
