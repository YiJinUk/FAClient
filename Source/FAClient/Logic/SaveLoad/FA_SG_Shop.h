// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "GameFramework/SaveGame.h"
#include "FA_SG_Shop.generated.h"

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_SG_Shop : public USaveGame
{
	GENERATED_BODY()
	
public:
	void SGSaveData(FInfoGame& s_info_game);
public:
	UPROPERTY()
		TArray<FString> code_ribbons;
};
